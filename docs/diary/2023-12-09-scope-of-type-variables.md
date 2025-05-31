---
title: Scope of type variables
date: 2023-12-09
---

How to handle the scope of type variables,
which should go across quote boundaries.

```
'list_match [ :a list_t [ :b ] [ :a list_t :a -- :b ] -- :b ] claim
```

If we implement it without any consideration about performance,
before applying a program, we can clone and rename the variables.

```
[ :a list_t [ :b ] [ :a list_t :a -- :b ] -- :b ]
```

to get

```
[ :a₁ list_t [ :b₁ ] [ :a₁ list_t :a₁ -- :b₁ ] -- :b₁ ]
```

and next time to get

```
[ :a₂ list_t [ :b₂ ] [ :a₂ list_t :a₂ -- :b₂ ] -- :b₂ ]
```

But if we implement it in C, we should
come up with a clever way to
do it with good performance.

Maybe one level of indirection can do the job.

------

I should just copy and rename first!
