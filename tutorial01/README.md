# 笔记

## Cmake

[cmake_minimum_required](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html)

```
cmake_minimum_required (VERSION 3.10)
```

设置工程的最小要求 Cmake 版本。

其中 FATAL_ERROR 参数在 cmake 2.6 到更高的版本已经被忽略了。

[add_library](https://cmake.org/cmake/help/latest/command/add_library.html)

```
add_library(leptjson leptjson.c)
```

使用指定的源文件生成库添加到工程中。其生成的库文件名根据平台不同而不同。

cmake3.11 版本以后，源文件可以在之后的 `target_source()`中指定。

库类型：

STATIC：静态库，对象文件合集，在程序链接期和目标链接。

SHARED：动态库，在运行时动态加载和链接。

MODULE：`libraries are plugins that are not linked into other targets but may be loaded dynamically at runtime using dlopen-like functionality.`

CMake 文件中没有指定库类型，那么默认是 `STATIC`。

[if](https://cmake.org/cmake/help/latest/command/if.html)

```
if(<条件一>)
  <条件一为真执行语句>
elseif(<条件二>) # optional block, can be repeated
  <条件二为真执行语句>
else()              # optional block
  <其他情况执行语句>
endif()
```

```
if(<变量或者字符串> MATCHES 正则表达式)
示例：
if ("zhanghui" MATCHES "zhang")
    message( STATUS "zhanghui." )
endif()
# 结果会输出 "zhanghui."

```

CMAKE_C_COMPILER_ID 是全局变量，是Cmake 检测到当前平台使用的 c 语言编译器。

[message](https://cmake.org/cmake/help/latest/command/message.html)

```
message( STATUS "c compiler id is ${CMAKE_C_COMPILER_ID}" )
```

语法：

```
message([<mode>]"message text"...)
```

mode 模式可以指定

1. FATAL_ERROR：Cmake error，会终止进程或者生成
2. WARNING：继续进程，只是警告
3. STATUS：打印一写配置过程中关心的信息

CMAKE_`<LANG>`_FLAGS ：全局变量，LANG可以是：`C`，`CXX`, `CUDA`等，指定编译类型的所有参数选项。

target_link_libraries(leptjson_test leptjson) : 指定在链接给定目标和/或其依赖时使用的库或标志。

json 的文本解析器需要保证一致性，不应该接受任何不符合 json 文本格式结构的输入。


## 预处理
指令以 # 开始，第一个换行符结束，若需要换行，但是指令不结束，可以在末尾使用 `\`，继续定义。

注意：宏可能不止一次的计算传入的参数</br>
```cpp
#include <stdio.h>

#define MAX(x,  y) (((x) > (y)) ? (x) : (y))

int main() 
{
    int i = 1;
    int j = 23;
    printf("max(i, j++) = %d, now j = %d\n", MAX(i, j++), j);
    // 这里对 max 的调用就是 ((i) < (j++)) ? (i) : (j++);
    // 因为 i 小于 j 故，这里 j 会执行自增两次
    // 结果：max(i, j++) = 24, now j = 25
    return 0;
}
```

```
# 记号
n 之前的#运算符通知预处理器根据PRINT_INT 的参数创建一个字符串字面量。
#define PRINT_N(n) printf(#n " = hello %d\n", n)
// j / i = hello 6

## 记号
// 组合形成新的变量，没啥用。。不知道怎么调用这个宏函数
#define GNERIC_MAX(type) \
type type##_max(type x, type y) { \
    return x > y ? x : y; \
}
```

宏定义的作用范围通常到出现这个宏的文件末尾。</br>
`#undef 宏名` 取消一个已经定义的宏以便于重新定义这个宏。</br>
记得给宏添加必要的括号。
```cpp
#define TEST1 2 + 33
#define PRINT_N(n) printf(#n " = %d\n", n)

PRINT_N(TEST1 * 2);
// result = TEST1 * 2 = 68

#define SCALE(x) (x * 1.11)
PRINT_F(SCALE(i + 4));
// SCALE(i + 4) = 8.44
// SCALE(i + 4 * 1.11)
// correct macro
#define SCALE(x) ((x) * 1.11)

// 宏定义函数
#define ECHO(s) \
    do { \
        gets(s); \
        puts(s); \
    } while(0)

#define DISP2(func, x, y) printf("Rectangle width is %d, height is %d, Area is %d\n", x, y, func(x, y))

int area(int x, int y) {
    return x * y;
}

DISP2(area, 55, 10);
```

因为 C 语言没有 C++ 的命名空间（namespace）功能，一般会使用项目的简写作为标识符的前缀。通常枚举值用全大写（如 LEPT_NULL），而类型及函数则用小写（如 lept_type）。

JSON 是一个树形结构，我们最终需要实现一个树的数据结构，每个节点使用 lept_value 结构体表示，我们会称它为一个 JSON 值（JSON value）。

在这个 JSON 语法子集下，我们定义 3 种错误码：

- 若一个 JSON 只含有空白，传回 LEPT_PARSE_EXPECT_VALUE。
- 若一个值之后，在空白之后还有其他字符，传回 LEPT_PARSE_ROOT_NOT_SINGULAR。
- 若值不是那三种字面值，传回 LEPT_PARSE_INVALID_VALUE。

leptjson 是一个手写的递归下降解析器[recursive descent parser](http://www.cs.binghamton.edu/~zdu/parsdemo/recintro.html)