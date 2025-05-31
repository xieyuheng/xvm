---
title: Algebraic data type
author: Xie Yuheng
date: 2023-12-03
---

We need to design a runtime algebraic data type,
and also keep it type checkable.

Designing new syntax like `data` and `match` in lisp feels effortless,
but how should we design new syntax for concatenative language?

```scheme
(data List ((E U)) ()
  (nil () (List E))
  (:: ((e E) (es (List E))) (List E))
  ind-List)
```

```scheme
(claim length
  (Pi ((E U))
    (-> (List E) Nat)))

(define length
  (lambda (E es)
    (match es
      (nil zero)
      ((:: x xs) (add1 (length xs))))))
```

For the runtime, all we need is a `data_t` type,
which have the type tag and case tag.

```
'list_t [ type_t -- type_t ] claim
'null [ -- :a list_t ] claim
'cons [ :a :a list_t -- :a list_t ] claim

'list_lenght [
  'null [ zero ]
  'cons [ swap drop list_length add1 ]
  'list_t match
] define
```

if we do not care about type, only need runtime tagged data:

```
'list_t datatype_define
  'null 0 arity_case
  'cons 2 arity_case
datatype_close
```

for type maybe:

```
'list_t [ type_t -- type_t ] datatype_define
  'null [ -- :a list_t ] case
  'cons [ :a :a list_t -- :a list_t ] case
datatype_close
```

maybe like `define` vs. `claim`,
we should use untyped `datatype_define`
and `claim` the type separately.
