#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define STACKSIZE 100
#define STACKINCREMENT 10
typedef int ElemType;
typedef int Position;
typedef enum {
    false, true
} Bool;
//顺序存储栈
typedef struct myStack {
    int *stackSize;
    //position 位于最后元素的下一个（将要入栈的位置）
    Position *position;
    ElemType *data;
} Stack;
//链式存储队列
//具有头节点的队列：从头节点入，从最末尾节点出
typedef struct QueueNode *PtrToQueueNode;
struct QueueNode {
    ElemType data;
    PtrToQueueNode next;
};

/**
 * 初始化栈
 * @param stackSize
 * @return 一个栈结构，具有大小、空栈、当前位置
 */
Stack InitStack(int stackSize);

/**
 * 入栈
 * @param elem 数据
 * @param stack 栈
 * @return 成功true，失败false
 */
Bool Push(ElemType elem, Stack stack);

/**
 * 出栈
 * @param stack 栈
 * @return 出栈的数据
 */
ElemType Pop(Stack stack);

/**
 * 初始化队列
 * @return 队列头节点
 */
PtrToQueueNode InitQueueNode();

/**
 * 入队列
 * @param queue 队列头节点
 * @param elem 入队元素
 * @return 成功true，失败false
 */
Bool EnQueue(ElemType elem, PtrToQueueNode queue);

/**
 * 出队列
 * @param queue
 * @return 出队列的数据
 */
ElemType DeQueue(PtrToQueueNode queue);

/**
 * 释放整个链表
 * @param list
 */
void FreeList(PtrToQueueNode list);

int main() {
    int num;
    int i, stackCnt = 0, queueCnt = 0;
    Stack stack = InitStack(STACKSIZE);
    PtrToQueueNode queue = InitQueueNode();
    while (scanf("%d", &num) != EOF) {
        if (num > 0) {
            Push(num, stack);
            stackCnt++;
        } else {
            EnQueue(num, queue);
            queueCnt++;
        }
    }
    for (i = 0; i < stackCnt; ++i) {
        printf("%5d", Pop(stack));
    }
    printf("\n");
    for (i = 0; i < queueCnt; ++i) {
        printf("%5d", DeQueue(queue));
    }
    //莫名奇妙需要这个
    printf("\n");
    free(stack.position);
    free(stack.stackSize);
    free(stack.data);
    FreeList(queue);
    return 0;
}

Stack InitStack(int stackSize) {
    Stack stack;
    stack.stackSize = (int *) malloc(stackSize * sizeof(int));
    *stack.stackSize = stackSize;
    //初始化位置在第一个
    stack.position = (int *) malloc(stackSize * sizeof(int));
    *stack.position = 0;
    stack.data = (ElemType *) malloc(stackSize * sizeof(ElemType));
    return stack;
}

Bool Push(ElemType elem, Stack stack) {
    //栈满多分配
    if (*stack.position >= *stack.stackSize) {
        stack.data = (ElemType *) realloc(stack.data, (*stack.stackSize + STACKINCREMENT) * sizeof(ElemType));
        *stack.stackSize += STACKINCREMENT;
    }
    stack.data[*stack.position] = elem;
    *stack.position = *stack.position + 1;
    return true;
}

ElemType Pop(Stack stack) {
    //栈空报错
    if (*stack.position == 0) {
        printf("stack empty");
        exit(0);
    }
    *stack.position = *stack.position - 1;
    ElemType data = stack.data[*stack.position];
    return data;
}

PtrToQueueNode InitQueueNode() {
    PtrToQueueNode queue = (PtrToQueueNode) malloc(sizeof(struct QueueNode));
    queue->next = NULL;
    return queue;
}

Bool EnQueue(ElemType elem, PtrToQueueNode queue) {
    PtrToQueueNode tempNode = (PtrToQueueNode) malloc(sizeof(struct QueueNode));
    tempNode->data = elem;
    tempNode->next = NULL;
    while (queue->next != NULL) {
        queue = queue->next;
    }
    queue->next = tempNode;
    return true;
}

ElemType DeQueue(PtrToQueueNode queue) {
    //队列为空
    if (queue->next == NULL) {
        exit(0);
    }
    PtrToQueueNode tempNode = queue->next;
    queue->next = queue->next->next;
    ElemType reData = tempNode->data;
    free(tempNode);
    return reData;
}

void FreeList(PtrToQueueNode list) {
    PtrToQueueNode temp;
    while (list != NULL) {
        temp = list->next;
        free(list);
        list = temp;
    }
}