typedef int Postion;

/*双堆栈*/
/*从两头往中间长，相遇即满*/
typedef struct DSNode* PtrToDSNode;
struct DSNode {
    int* data;
    Postion top1;
    Postion top2;
    int MaxSize;
};
typedef PtrToDSNode dstack;

/*创建栈*/
dstack CreateStack(int MaxSize) {
    dstack s = (dstack)malloc(sizeof(struct DSNode));
    s->data  = (int*)malloc(sizeof(int));
    s->MaxSize = MaxSize;
    s->top1 = -1;
    s->top2 = -1;
    return s;
}