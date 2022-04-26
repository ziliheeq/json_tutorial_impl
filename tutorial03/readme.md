从零开始的 JSON 库教程（三）：

在 C 语言中，数组长度、索引值最好使用 size_t 类型，而不是 int 或 unsigned。

内存分配函数 malloc 函数返回的指针就是 void * 型，用户在使用这个指针的时候，要进行强制类型转换，也就是显式说明该指针指向的内存中是存放的什么类型的数据 (int *)malloc(1024) 表示强制规定 malloc 返回的 void* 指针指向的内存中存放的是一个个的 int 型数据。