c 语言中由于没有定义布尔类型，至少`c89`标准没有。

可以采用枚举([enum](https://en.cppreference.com/w/c/language/enum))的方式自定义布尔类型。
```c
typedef enum { false, true } bool;

bool func1(int a, int b) {
    return a == b;
}

int main() {
    printf("a == b ? %d\n", func1(3, 2));
    printf("a == b ? %d\n", func1(3, 3));
    return 0;
}
/*
a == b ? 0
a == b ? 1
*/
```