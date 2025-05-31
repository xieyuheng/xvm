---
title: object in xasm
date: 2024-12-21
---

问题：

- 如何处理函数中的 object？
- 尤其是 const object。

方案 A：

- 在编译时在 heap 中生成 object，保存指针到当前位置。

  ```
  @user-name <comptime> "xieyuheng" here </comptime> end
  ```

  这要求在 assemble 的过程中可以运行 xvm。

方案 B：

- object 只在运行时存在。
  不处理 const object，每次都生成新的 object。
  object 相关函数都带有 linear 语义，
  在需要的时候主动调用相关的 dup 和 free。

  ```
  @main "xieyuheng" string-dup string-print string-free end
  ```

方案 C：

- 放弃任意的 object in heap，
  只支持 string 和 struct。
  struct 需要在汇编中定义。
  像 C 的 stack frame 一样，
  `frame_t` 有一片区域用来保存 local struct。
  struct-spec 用类似 inet 中 node-spec 的方案来解决。

  ```
  @user/struct :name! :age END
  @main "xieyuheng" 123 &user NEW END
  ```

讨论：

- 是否应该放弃 tagged value？
  如果放弃，就完全不用考虑 heap memory 的问题了。
  如果放弃了，如何实现 inet？
  可以在实现 inet 的编译器的时候，再加上 tagged value。

- 可以是「方案 C」 和「方案 B」的结合。
  我们很难放弃 xasm + xvm 的方案，
  因为考虑 inet 的实现，就算是用 lisp 语法，也要编译的 stack vm。
  既然觉得可以有 inet-asm，那么 xasm 中也可以加 struct。

  - 模仿 jai。
    struct 可以标记对 field 的 ownership，
    这样就可以递归的 free。

  - 如何处理 array 对元素的 ownership？
    learn from jai。
