[maybe] move lexicon out again -- to simplify dependance
[maybe] move ram out -- to simplify dependance

[lexicon] lexicon_test -- setup

[lexicon] lexicon_load -- from blob in .lexi format
[lexicon] lexicon_test -- test lexicon_load
[xdisasm] xdisasm_t -- has lexicon
[xdisasm] xdisasm_run
[xdisasm] xdisasm_step
[xdisasm] xdisasm_disasm -- call xdisasm_run

[xemu] OP_OK -- execute report value stack, frame stack, disasm the context

[xemu] frame has locals -- 32 max
[opcode] LOCAL_SET LOCAL_GET -- just use int as index
[xasm] [maybe] use $1! and $1 for LOCAL_SET and LOCAL_GET

[xemu] xsymbol
[xemu] [maybe] xsymbol_inline -- within 64bits -- max length is 7 bytes
[xemu] [maybe] xsymbol_long

[xemu] xstring

[xemu] xobject -- first field must be kind
[xemu] xstruct

[xemu] xtuple
[xemu] xchar

[xemu] [maybe] use utf8-style opcode encoding -- to be extensible

[motivation] at worst, xvm will provide inet tagged primitive values
