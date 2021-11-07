#include <stdio.h>
#include <stdlib.h>

typedef struct node *PtrToNode;
typedef struct node {
    int num;
    PtrToNode next;
} Node;

/**
 * 以一个非“-1”数据创建节点，若是-1则返回NULL
 * @param num 非-1
 * @return 节点
 */
PtrToNode CreateNode(int num);

/**
 * 以输入创建新的链表带头节点
 * @return 链表头节点
 */
PtrToNode CreateNodeList();

/**
 * 非降序合并两个链表
 * @param list1 第一个链表
 * @param list2 第二个链表
 * @return 新链表
 */
PtrToNode MergeList(PtrToNode list1, PtrToNode list2);

/**
 * 打印链表，形式num1 num2 ... numn
 * @param list 有头节点链表
 */
void PrintList(PtrToNode list);

int main() {
    PtrToNode list1 = CreateNodeList();
    PtrToNode list2 = CreateNodeList();
    PtrToNode list3 = MergeList(list1, list2);
    PrintList(list3);
    return 0;
}

PtrToNode CreateNode(int num) {
    if (num == -1) {
        return NULL;
    }
    PtrToNode node = (PtrToNode) malloc(sizeof(PtrToNode));
    node->num = num;
    node->next = NULL;
    return node;
}

PtrToNode CreateNodeList() {
    int num;
    PtrToNode head = CreateNode('s');
    PtrToNode start = head;
    scanf("%d", &num);
    while (num != -1) {
        start->next = CreateNode(num);
        start=start->next;
        scanf("%d", &num);
    }
    return head;
}

PtrToNode MergeList(PtrToNode list1, PtrToNode list2) {
    PtrToNode start1 = list1->next;
    PtrToNode start2 = list2->next;
    PtrToNode head = CreateNode('s');
    PtrToNode start3 = head;
    while (start1 != NULL && start2 != NULL) {
        if (start1->num <= start2->num) {
            start3->next = CreateNode(start1->num);
            start1 = start1->next;
        } else {
            start3->next = CreateNode(start2->num);
            start2 = start2->next;
        }
        start3 = start3->next;
    }
    if (start1 != NULL) {
        while (start1 != NULL) {
            start3->next = CreateNode(start1->num);
            start1 = start1->next;
            start3 = start3->next;
        }
    }
    if (start2 != NULL) {
        while (start2 != NULL) {
            start3->next = CreateNode(start2->num);
            start2 = start2->next;
            start3 = start3->next;
        }
    }
    return head;
}

void PrintList(PtrToNode list) {
    list = list->next;
    if(list==NULL){
        printf("NULL\n");
        return;
    }

    int cnt = 0;
    while (list != NULL) {
        if (cnt++) {
            printf(" ");
        }
        printf("%d", list->num);
        list = list->next;
    }
    printf("\n");
}