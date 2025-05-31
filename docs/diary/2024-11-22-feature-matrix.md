---
title: feature matrix
date: 2024-11-22
---

| plan      | tagged vs. raw | GC  | type system  | generic  |
|           | about value     |     | maybe linear | dispatch |
|-----------|-----------------|-----|--------------|----------|
| initial   | raw             | no  | no           | no       |
| revised   | raw             | no  | yes          | no       |
| revised^2 | tagged          | yes | no           | no       |
| revised^3 | tagged          | no  | no           | yes      |

想要加入 generic dispatch，
但是我不知道应该如何设计语法。

如何在定义一个 generic function 的时候描述 predicates?

- stack: 1 2 "a"
- predicate: int? int? string?

总不能用一段 quoted program，
在里面置换参数来完成整体的 predicate 判断。

也许可以以 `( predicate predicate ... )` 为运行时的判断。

```
= add ( int? int? ) ...
= add ( int? vector? ) ...
```

so that i can:

```
= length ( null? ) ...
= length ( cons? ) ...
```

[2024-11-25] 可以选择 revised^3，并且实现上面的 generic function。

- 每个 value 都是 1-byte tag + 8-byte data。
- 可能可以叫做 niun -- 代表九。
- 也可以不实现 generic function，只是做一个 9-byte vm。
  - 1-byte opcode -- 感觉都用不上这么多编码能力。
