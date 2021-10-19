#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType data;
    PtrToNode next;
};
typedef enum {
    false, true
} Bool;

/**
 * 初始化链表（循环单列表），创建头节点
 * @return 一个头节点
 */
PtrToNode InitListLoop();

/**
 * 在指定节点后插入节点
 * @param node 位置节点
 * @param insertNode 需要插入的节点
 * @return 成功true，失败false
 */
Bool InsertNode(PtrToNode node, PtrToNode insertNode);

/**
 * 从链表中移除某节点
 * @param list 链表
 * @param node 节点
 * @return 成功true，失败false
 */
Bool RemoveNode(PtrToNode list, PtrToNode node);

/**
 * 以某个数据创建节点
 * @param element 数据
 * @return 节点指针
 */
PtrToNode CreateNew(ElementType element);

int main() {
    PtrToNode list = InitListLoop();
    PtrToNode start = list;
    PtrToNode node;
    PtrToNode newStart;
    int total,gap;
    scanf("%d %d", &total, &gap);
    //无头节点，头节点赋值
    list->data = 1;
    //创建循环单链表
    for (int i = 2; i <= total; ++i) {
        node = CreateNew(i);
        InsertNode(start, node);
        start = start->next;
    }
    //使之成为循环链表
    start = list;
    while (start->next != start) {
        for (int j = 0; j < gap-1; ++j) {
            start = start->next;

        }
        newStart=start->next;
        printf("%4d",start->data);
        RemoveNode(start,start);
        free(start);
        start=newStart;
    }
    printf("%4d",start->data);
    free(start);
}

PtrToNode InitListLoop() {
    PtrToNode list = (PtrToNode) malloc(sizeof(struct Node));
    if (list == NULL) { exit(1); }
    list->next = list;
    return list;
}

Bool InsertNode(PtrToNode node, PtrToNode insertNode) {
    if (node == NULL || insertNode == NULL) {
        return false;
    }
    insertNode->next = node->next;
    node->next = insertNode;
    return true;
}

Bool RemoveNode(PtrToNode list, PtrToNode node) {
    PtrToNode before = list;
    if ( list == NULL || node == NULL) {
        //不可移除头节点，以及其他错误
        return false;
    }
    //定位到node前一个
    while (before->next != node) {
        before = before->next;
    }
    before->next = node->next;
    return true;
}

PtrToNode CreateNew(ElementType element) {
    PtrToNode newPtrNode = (PtrToNode) malloc(sizeof(struct Node));
    if (NULL == newPtrNode) { exit(1); }
    newPtrNode->data = element;
    newPtrNode->next = NULL;
    return newPtrNode;
}