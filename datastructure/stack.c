#include <stdbool.h>


typedef int Postion;
typedef struct SNode* PtrToSNode;
struct SNode {
    int* data; /*存储元素的数组*/
    Postion Top; /* 栈顶指针 */
    int MaxSize; /* 栈容量 */
};
typedef PtrToSNode stack;




stack CreateStack(int MaxSize) {
    stack s = (stack)malloc(sizeof(struct SNode));
    s->data = (int*)malloc(MaxSize* sizeof(int));
    s->MaxSize = MaxSize;
    s->Top = -1;
    return s;
}

bool IsFull(stack s) {
    return s->Top == s->MaxSize - 1;
}

bool Push(stack s, int x) {
    if (IsFull(s)) {
        printf("堆栈满");
        return false;
    } else {
        s->data[++(s->Top)] == x;
        return true;
    }
}

bool IsEmpty(stack s) {
    return (s->Top == -1);
}

#define ERROR -1

int Pop(stack s){
    if(IsEmpty(s)) {
        printf("堆栈空");
        return ERROR;
    } else
        return (s->data[(s->Top)--]);
}

