---
title: using colon keyword instead of quote symbol
author: Xie Yuheng
date: 2024-10-21
---

也许用多种用途的 :keyword 而不是 'symbol 可以让语法设计更好。

```
:abs [ dup 0 lt [ -1 mul ] if ] define
:gcd [ dup2 eq [ drop ] [ dup2 sub abs gcd ] if_else ] define
```

vs.

```
'abs [ dup 0 lt [ -1 mul ] if ] define
'gcd [ dup2 eq [ drop ] [ dup2 sub abs gcd ] if_else ] define
```

record 也可以重用这种语法。
