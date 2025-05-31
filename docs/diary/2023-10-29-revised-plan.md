---
title: Revised plan
author: Xie Yuheng
date: 2023-10-29
---

Let's design a scripting language for scalable c.

We can try to implement linear type,
maybe without variables, forth is naturally linear type?

We will need to implement borrowing of pointer.
Because a pointer might be passed to subroutine,
while subroutine should not delete the pointer

If linear type does not work we go back to simple type.

------

[2024-11-21] 不需要像 rust 一样实现 pointer 的 borrowing，
可以直接让 subroutine 把 borrow 的东西还回来到栈中。

其实不能单说 linear type，
而应该说 linear simple type。
并且 linear simple type 比 non-linear simple type 要更简单。
