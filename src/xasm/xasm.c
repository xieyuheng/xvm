#include "index.h"

xasm_t *
xasm_new(void) {
    xasm_t *self = new(xasm_t);
    size_t init_ram_size = 64 * 1024;
    self->ram = ram_new(init_ram_size);
    self->lexer = lexer_new();
    self->lexer->line_comment = "//";
    self->lexicon = lexicon_new();
    self->cursor = 0;
    self->ram_expanding_size = init_ram_size;
    self->xaddress_blank_stack = stack_new_with(
        (destroy_fn_t *) xaddress_blank_destroy);
    return self;
}

void
xasm_destroy(xasm_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        xasm_t *self = *self_pointer;
        ram_destroy(&self->ram);
        lexer_destroy(&self->lexer);
        lexicon_destroy(&self->lexicon);
        stack_destroy(&self->xaddress_blank_stack);
        free(self);
        *self_pointer = NULL;
    }
}

static void
xasm_maybe_expend(xasm_t *self, size_t required_size) {
    if (self->cursor + required_size < self->ram->size)
        return;

    ram_expand(self->ram, self->ram->size + self->ram_expanding_size);
}

static void
xasm_emit_byte(xasm_t *self, uint8_t byte) {
    xasm_maybe_expend(self, sizeof(uint8_t));

    ram_set_byte(self->ram, self->cursor, byte);
    self->cursor += sizeof(uint8_t);
}

static void
xasm_emit_value(xasm_t *self, value_t value) {
    xasm_maybe_expend(self, sizeof(value_t));

    ram_set_value(self->ram, self->cursor, value);
    self->cursor += sizeof(value_t);
}

static void
fill_in_all_xaddress_blanks(xasm_t *self) {
    while (!stack_is_empty(self->xaddress_blank_stack)) {
        xaddress_blank_t *xaddress_blank = stack_pop(self->xaddress_blank_stack);
        lexeme_t *lexeme = hash_get(self->lexicon->lexeme_hash, xaddress_blank->key);
        if (!lexeme) {
            fprintf(
                stderr,
                "[fill_in_all_xaddress_blanks] undefined key: %s\n",
                xaddress_blank->key);
            exit(1);
        }

        ram_set_value(self->ram, xaddress_blank->address, xaddress(lexeme->address));
    }
}

void
xasm_run(xasm_t *self, const char *string) {
    self->lexer->string = string;
    lexer_run(self->lexer);

    token_t *token = list_first(self->lexer->token_list);
    while (token) {
        xasm_step(self, token);
        token = list_next(self->lexer->token_list);
    }

    fill_in_all_xaddress_blanks(self);

    list_destroy(&self->lexer->token_list);
}

static bool
step_opcode(xasm_t *self, const token_t *token) {
    if (!string_is_mnemonic(token->string))
        return false;

    xasm_emit_byte(self, mnemonic_to_opcode(token->string));
    return true;
}

static bool
step_constant(xasm_t *self, const token_t *token) {
    if (!string_is_constant_value(token->string))
        return false;

    xasm_emit_value(self, string_to_constant_value(token->string));
    return true;
}

static bool
step_xint(xasm_t *self, const token_t *token) {
    if (string_is_xint(token->string)) {
        xasm_emit_value(self, xint(string_parse_xint(token->string)));
        return true;
    }

    return false;
}

static bool
step_xfloat(xasm_t *self, const token_t *token) {
    if (string_is_double(token->string)) {
        xasm_emit_value(self, xfloat(string_parse_double(token->string)));
        return true;
    }

    return false;
}

static bool
step_label(xasm_t *self, const token_t *token) {
    if (!string_starts_with(token->string, "@") ||
        string_count_char(token->string, '@') != 1)
        return false;

    size_t length = string_length(token->string);
    char *key = string_slice(token->string, 1, length);
    lexeme_t *lexeme = lexeme_new(key, self->cursor);
    bool ok = hash_set(self->lexicon->lexeme_hash, key, lexeme);
    if (ok) return true;

    fprintf(
        stderr,
        "[step_label] label already used: %s\n",
        token->string);
    exit(1);
}

static void
step_xaddress_aux(xasm_t *self, char *key) {
    stack_push(self->xaddress_blank_stack,
               xaddress_blank_new(key, self->cursor));
    self->cursor += sizeof(value_t);
}

static bool
step_xaddress(xasm_t *self, const token_t *token) {
    if (!string_starts_with(token->string, "&") ||
        string_count_char(token->string, '&') != 1)
        return false;

    size_t length = string_length(token->string);
    char *key = string_slice(token->string, 1, length);
    step_xaddress_aux(self, key);
    return true;
}

static bool
step_call(xasm_t *self, const token_t *token) {
    xasm_emit_byte(self, OP_CALL);
    step_xaddress_aux(self, string_copy(token->string));
    return true;
}

void
xasm_step(xasm_t *self, const token_t *token) {
    if (step_opcode(self, token)) return;
    if (step_constant(self, token)) return;
    if (step_xint(self, token)) return;
    if (step_xfloat(self, token)) return;
    if (step_label(self, token)) return;
    if (step_xaddress(self, token)) return;
    if (step_call(self, token)) return;

    fprintf(
        stderr,
        "[xasm_step] unknown token: %s\n",
        token->string);
}

blob_t *
xasm_dump(xasm_t *self) {
    blob_t *blob = blob_new(self->cursor);
    blob_copy_from(blob, self->ram->bytes);
    return blob;
}

blob_t *
xasm_asm(const char *string) {
    xasm_t *self = xasm_new();
    xasm_run(self, string);
    blob_t *blob = xasm_dump(self);
    xasm_destroy(&self);
    return blob;
}
