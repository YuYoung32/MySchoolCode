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

/**
 * 约瑟夫环游戏
 * @param head 传入循环单链表首节点（无头节点）
 * @param gap 每次的报数
 * @return 出链顺序组成的新循环链表
 */
PtrToNode JosephRingGame(PtrToNode list, int gap);

/**
 * 打印无头节点循环单链表，形式：%4d
 * @param list
 */
void PrintListLoop(PtrToNode list);

/**
 * 释放循环单链表
 * @param list 链表
 */
void FreeListLoop(PtrToNode list);

int main() {
    PtrToNode list = InitListLoop();
    PtrToNode newList;
    //复制首节点
    PtrToNode start = list;
    PtrToNode node;
    int total, gap1, gap2;
    //消除头节点
    list->data = 1;
    scanf("%d", &total);
    scanf("%d", &gap1);
    scanf("%d", &gap2);
    for (int i = 2; i <= total; ++i) {
        node = CreateNew(i);
        InsertNode(start, node);
        start = start->next;
    }
    //链接头节点

    newList = JosephRingGame(list, gap1);
    newList = JosephRingGame(newList, gap2);
    PrintListLoop(newList);

    FreeListLoop(newList);

    return 0;

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
    if (list == NULL || node == NULL) {
        //不可移除头节点，以及其他错误
        return false;
    }
    //定位到node前一个
    while (before->next != node) {
        before = before->next;
    }
    //节点的next域未置空
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

PtrToNode JosephRingGame(PtrToNode list, int gap) {
    //这里的环是有头节点的,因为后续插入节点问题，要设置成有头节点
    PtrToNode newList = InitListLoop();
    //复制首节点便于操作
    PtrToNode start = list;
    PtrToNode newListStart = newList;
    //临时使用的节点
    PtrToNode newStart;
    //开始游戏
    while (start->next != start) {
        for (int j = 0; j < gap - 1; ++j) {
            start = start->next;
        }
        newStart = start->next;

        //注意这里的顺序
        //原链表移除,(不改变start的next域)
        RemoveNode(start, start);
        //向新链表插入节点
        InsertNode(newListStart, start);
        newListStart = newListStart->next;

        //新起点指定
        start = newStart;
    }
    //插入最后节点
    InsertNode(newListStart,start);
    newListStart = newListStart->next;
    //构成没有头节点的单循环链表，这一步是为了去除头节点
    newListStart->next = newList->next;

    //释放头节点
    PtrToNode temp=newList->next;
    free(newList);
    return temp;
}

void PrintListLoop(PtrToNode list) {
    PtrToNode head = list;
    //使用do-while结构，确保最后一个节点也能打印
    do{
        printf("%4d", head->data);
        head = head->next;
    } while (head!=list);
}

void FreeListLoop(PtrToNode list) {
    PtrToNode head=list;
    PtrToNode temp = NULL;
    while (list != head) {
        temp = list->next;
        free(list);
        list = temp;
    }
}
