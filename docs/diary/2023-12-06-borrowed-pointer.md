---
title: borrowed pointer
date: 2023-12-06
---

i found that, if i do no gc, and use linear type to handle resourses safely.
given:
[ l ] : [ int_t list_t ]
the type of dup and drop will be like:
[ l dup ] : [ int_t list_t int_t list_t borrowed_t ]
[ drop ] : [ :a borrowed_t -- ]
and i will need two kinds of match, one that free the target match, one that not borrowed_match.
for example, list_lenght should take borrowed list as target.
```
'list_lenght [
  'null [ zero ]
  'cons [ swap drop list_length add1 ]
  'list_t borrowed_match
] define
```
if the input of a function is borrowed pointer, the function does not need to free it.
