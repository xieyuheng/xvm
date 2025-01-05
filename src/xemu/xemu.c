#include "index.h"

xemu_t *
xemu_new(size_t ram_size) {
    xemu_t *self = new(xemu_t);
    self->ram = ram_new(ram_size);
    self->value_stack = stack_new();
    self->return_stack = stack_new_with((destroy_fn_t *) frame_destroy);
    return self;
}

void
xemu_destroy(xemu_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        xemu_t *self = *self_pointer;
        stack_destroy(&self->value_stack);
        stack_destroy(&self->return_stack);
        ram_destroy(&self->ram);
        free(self);
        *self_pointer = NULL;
    }
}

void
xemu_step(xemu_t *self) {
    if (stack_is_empty(self->return_stack))
        return;

    frame_t *frame = stack_pop(self->return_stack);
    if (frame_is_at_tail(frame, self->ram)) {
        frame_destroy(&frame);
        return;
    }

    opcode_t opcode = frame_fetch_opcode(frame, self->ram);
    execute(self, frame, opcode);
}

void
xemu_run_until(xemu_t *self, size_t base_length) {
    while (stack_length(self->return_stack) > base_length) {
        xemu_step(self);
    }
}

void
xemu_run(xemu_t *self) {
    while (!stack_is_empty(self->return_stack)) {
        xemu_step(self);
    }
}

void
xemu_emu(const blob_t *blob) {
    xemu_t *self = xemu_new(blob_size(blob));
    blob_copy_into(blob, self->ram->bytes);
    stack_push(self->return_stack, frame_new(0));
    xemu_run(self);
    xemu_destroy(&self);
}
