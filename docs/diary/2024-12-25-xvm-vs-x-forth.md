---
title: xvm vs x-forth
date: 2024-12-25
---

xvm 可能并不适合处理 struct 之类的定义。
x-forth 更适合。

forth 不用考虑 object in heap 的问题，更灵活。
比如 x-forth 可以通过 builtin function 来扩展，
而不用都处理成 opcode。

学习 forth 如何处理 struct

- 如果 XVM 在汇编中处理不好 struct，或者说编译时的对 definition 的构造，
  就切换到 x-forth。

- 感觉在设计 XVM layout bytes 的方式的时候，我的想象力有点太局限了。
  甚至没能解决 literal string 就想放弃。
  LIT-STRING <kind> <length> <byte> ...

- 也许应该区分 heap-object 和 object，
  每个 address 下都是一个 object，即第一个 byte 是一个 kind（类似 forth），
  这个 kind 决定了这个 object 在 CALL 的时候应该如何被解释。

x-forth -- tagged forth use define and end instead of : and ;

- 没有标点，为中文翻译做准备
