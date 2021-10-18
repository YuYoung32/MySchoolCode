#include <stdio.h>
typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode List;

//题解1，重建整个链表。
List Reverse(List L)
{
    //为后续空间分配提供模板
    struct Node mynode;

    //每次需要插入的节点
    PtrToNode NewNode = NULL;

    //新链表的结点
    PtrToNode AddNode = (PtrToNode)malloc(sizeof(mynode));

    //新链表的起点
    PtrToNode NewStart = AddNode;
    while (L != NULL)
    {
        NewNode = L;
        //定位到最后一个
        while (NewNode->Next != NULL)
        {
            NewNode = NewNode->Next;
        }
        AddNode->Data = NewNode->Data;
        AddNode->Next = (PtrToNode)malloc(sizeof(mynode));
        AddNode = AddNode->Next;
        NewNode = NULL;
    }
    return NewStart;
}

//题解2，将旧的链表链接到新链表，通过
List Reverse(List L)
{
    PtrToNode new = NULL;
    PtrToNode temp = NULL;
    while (L != NULL)
    {
        temp = L;
        
        temp->Next = new;
        new = temp;
        L = L->Next;
    }
    return new;
}