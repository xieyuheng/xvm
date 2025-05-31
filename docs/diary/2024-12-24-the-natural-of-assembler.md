---
title: the natural of assembler
date: 2024-12-24
---

汇编语言的本质是 layout bytes (or words)。

layout 的特点是，在其过程中，
可以用 label 标记 address，
并且可以引用被标记的 address。

这就要求有一个 assemble-time 的 symbol table。

我想要用这个 assemble-time 的东西来定义 struct，
并且在实现 inet 时要能扩展到定义 node。
和定义相关的东西，大部分是 assemble-time 的东西，
并且可能还需要一些 runtime 支持。

因此，汇编语言的本质是 layout bytes (or words)，
外加在 assemble-time 处理好对各种 definition 的构造。

只是通过 layout bytes 能处理好对各种 definition 的构造吗？
