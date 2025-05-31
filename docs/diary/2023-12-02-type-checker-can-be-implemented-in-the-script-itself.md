---
title: Type checker can be implemented in the script itself
author: Xie Yuheng
date: 2023-12-02
---

Type checker can be implemented in the script itself.

By doing this, we can:

- Keep the untyped runtime simple.
- Write the first non-trivial program in the script -- the type checker.

To do this, maybe we need to implement runtime algebraic data type first.

While doing this, we must make sure the type checker can be check by itself.
