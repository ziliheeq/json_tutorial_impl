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
