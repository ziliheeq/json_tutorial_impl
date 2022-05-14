# json_tutorial_impl

from [miloyip-json-tutorial](https://github.com/miloyip/json-tutorial)


## tutorial 05 

[教程地址](https://zhuanlan.zhihu.com/p/22804068)

由于 lept_value 内使用了自身类型的指针，我们必须前向声明（forward declare）此类型。
```cpp
// 前向声明
typedef struct lept_value lept_value;

struct lept_value {
    union {
        struct { lept_value* e; size_t size; }a;    /* array:  elements, element count */
        struct { char* s; size_t len; }s;           /* string: null-terminated string, string length */
        double n;                                   /* number */
    }u;
    lept_type type;
};
```

C 语言中，数组大小(size)和索引(index)的类型推荐使用`size_t`, 定义在头文件`stddef.h`。

[原因](https://stackoverflow.com/questions/6004415/why-size-t-when-int-would-suffice-for-the-size-of-an-array)

大致就是整数类型不只是`int`，还可能是`char`,`short`等，加上不同平台的整数类型宽度范围不同，而`size_t`宽度范围和平台相同(多少位32、64)

这张主要是数组元素的压栈和弹栈处理，有一点不习惯，还是得再学习一下[TCPL](https://www.amazon.com/Programming-Language-2nd-Brian-Kernighan/dp/0131103628) [下载](http://cslabcms.nju.edu.cn/problem_solving/images/c/cc/The_C_Programming_Language_%282nd_Edition_Ritchie_Kernighan%29.pdf)第四章那个简易计算机程序的方式。

头文件`ctype.h`，有函数`isdigit`:判断字符是否为数字, `tolower`：字母字符转换为小写。

一些机器上面，会将`char`类型数字最左边以为拓展为符号位，0表示正数，1表示负数。

gcc 是一种集成编译器发行，支持多种程序语言。

gcc 简单编译命令使用：`gcc test.c -o test`使用此命令即使用`gcc`编译器将源文件`test.c`编译链接成一个可执行文件`test`。

数据结构——堆栈

数据存储特点——后入先出，比如一叠盘子，用的话拿最上面一个，用完清洗之后放回去，也是防在最上面，这里就是堆栈的一个栈顶端点。 

栈是线性表，可以使用顺序和链式两种形式。

