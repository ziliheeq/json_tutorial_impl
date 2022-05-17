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

c 语言定义栈空间，顺序栈，一个一维数组存储数据、一个变量记录栈顶、一个变量记录容量
```c
typedef int Postion;
typedef struct SNode* PtrToSNode;
struct SNode {
    int* data; /*存储元素的数组*/
    Postion Top; /* 栈顶指针 */
    int MaxSize; /* 栈容量 */
};

typedef PtrToSNode Stack;
```

重点操作一：创建栈
```c
Stack CreateStack(int MaxSize) {
     /* 这里强制转换 malloc 分配的指针类型，malloc 返回时 void* 类型 */
    stack s = (Stack)malloc(sizeof(struct SNode));
    /* 此时 data 只是一个空指针，需要对他按 MaxSize 申请内存 */
    s->data = (int*)malloc(MaxSize* sizeof(int));
    return s;
}
```

重点操作二：入栈或压栈——`PUSH`

1. 判断栈是否已经满，
2. 若不满， Top + 1，并将新元素放在`data`数组的`Top`位置
3. 若满，返回`false`，压栈采用布尔值类型返回`bool`定义在头文件`stdbool.h`中
```c
/* 判断是否栈满 */
bool IsFull(stack s) {
    return s->Top == s->MaxSize - 1;
}

/* 压栈 */
bool Push(stack s, int x) {
    if (IsFull(s)) {
        printf("堆栈满");
        return false;
    } else {
        /* 将新元素放到数组 data 的 Top 位置 */
        s->data[++(s->Top)] == x;
        return true;
    }
}
```
重点操作三：弹栈——`POP`

1、首先判断当前栈是否为空

2、不空，返回`data[top]`，同时将top - 1

3、否则返回错误标志
```c
#define ERROR -1

int Pop(stack s){
    if(IsEmpty(s)) {
        printf("堆栈空");
        return ERROR;
    } else
        return (s->data[(s->Top)--]);
}
```
双堆栈
