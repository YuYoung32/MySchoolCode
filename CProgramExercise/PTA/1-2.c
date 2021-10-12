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
 * 初始化链表，创建头节点
 * @return 一个头节点
 */
PtrToNode InitList();

/**
 * 在指定节点后插入节点
 * @param node 位置节点
 * @param insertNode 需要插入的节点
 * @return 成功true，失败false
 */
Bool InsertNode(PtrToNode node, PtrToNode insertNode);

/**
 * 找到链表中第一个data域大于某个节点之前的位置
 * @param list 需要查找的链表
 * @param node 节点
 * @return 节点指针
 */
PtrToNode FindBig(PtrToNode list, PtrToNode node);

/**
 * 以某个数据创建节点
 * @param element 数据
 * @return 节点指针
 */
PtrToNode CreateNew(ElementType element);

/**
 * 以”data1->data2->data3“形式打印链表
 * @param list 链表
 * @return 成功true，失败false
 */
Bool PrintList(PtrToNode list);

/**
 * 释放整个链表
 * @param list 链表
 */
void FreeList(PtrToNode list);

/**
 * 获得链表的最后一个节点
 * @param list 链表
 * @return 最后一个节点
 */
PtrToNode FindLast(PtrToNode list);

int main() {
    ElementType num;
    Bool result = false;
    PtrToNode node = NULL;
    PtrToNode position = NULL;
    PtrToNode positiveList = InitList();
    PtrToNode negativeList = InitList();
    while (scanf("%d", &num) != -1) {
        if (num >= 0) {
            node = CreateNew(num);
            position = FindBig(positiveList, node);
            result = InsertNode(position, node);
        } else if (num < 0) {
            //不包括0的判定
            node = CreateNew(num);
            position = FindBig(negativeList, node);
            result = InsertNode(position, node);
        }
//        if (result == false) {
//            printf("insert false at main\n");
//        }
    }
    PrintList(positiveList);
    printf("\n");
    PrintList(negativeList);
    //相对于1-1改变的部分
    printf("\n");
    PtrToNode newPtrToNode = negativeList;
    PtrToNode negLast= FindLast(negativeList);
    negLast->next=positiveList->next;
    PrintList(newPtrToNode);
    free(positiveList);
    FreeList(newPtrToNode);
    return 0;
}

PtrToNode InitList() {
    PtrToNode newList = (PtrToNode) malloc(sizeof(struct Node));
    if (NULL == newList) { exit(1); }
    newList->next = NULL;
    return newList;//头节点
}

Bool InsertNode(PtrToNode node, PtrToNode insertNode) {
    if (node == NULL || insertNode == NULL) {
        return false;
    }
    insertNode->next = node->next;
    node->next = insertNode;
    return true;
}

PtrToNode FindBig(PtrToNode list, PtrToNode node) {
    PtrToNode beforeTargetPtrToNode = list;
    PtrToNode targetPtrToNode = list->next;
    ElementType compareData = node->data;
    while (targetPtrToNode != NULL && targetPtrToNode->data < compareData) {
        beforeTargetPtrToNode = targetPtrToNode;
        targetPtrToNode = targetPtrToNode->next;
    }
    return beforeTargetPtrToNode;
}

PtrToNode CreateNew(ElementType element) {
    PtrToNode newPtrNode = (PtrToNode) malloc(sizeof(struct Node));
    if (NULL == newPtrNode) { exit(1); }
    newPtrNode->data = element;
    newPtrNode->next = NULL;
    return newPtrNode;
}

Bool PrintList(PtrToNode list) {
    if (list == NULL || list->next == NULL) {
        //平台要求空链表也要打印
        printf("\n");
        return false;
    }
    PtrToNode pList = list->next;

    while (pList->next != NULL) {
        printf("%d->", pList->data);
        pList = pList->next;
    }
    printf("%d", pList->data);
    printf("\n");
    return true;
}

void FreeList(PtrToNode list) {
    PtrToNode temp = NULL;
    while (list != NULL) {
        temp = list->next;
        free(list);
        list = temp;
    }
}

PtrToNode FindLast(PtrToNode list) {
    PtrToNode lastNode = list;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    return lastNode;
}

