#include <stdio.h>
#include <stdlib.h>

#define ERROR NULL
typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode
{
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;


Position Find(List L, ElementType X);
List Insert(List L, ElementType X, Position P);
List Delete(List L, Position P);

// 已通过
//初始思路
Position Find(List L, ElementType X)
{
    while (L != NULL)
    {
        if (L->Data == X)
        {
            return L;
        }
        L = L->Next;
    }
    return ERROR;
}
List Insert(List L, ElementType X, Position P)
{
    //第一个位置插入，题意是可以在空链表插入，也可以在末尾插入。
    //空链表插入或首位置插入
    if (P == L)
    {
        PtrToLNode newNode = (List)malloc(sizeof(struct LNode));
        newNode->Data = X;
        newNode->Next = L;
        L = newNode;
        
        return L;
    }
    PtrToLNode head = L;
    PtrToLNode tail = L->Next;
    if (P == NULL)
    {
        while (head->Next!=NULL)
        {
            head=head->Next;
        }
        
        PtrToLNode newNode = (List)malloc(sizeof(struct LNode));
        newNode->Data = X;
        newNode->Next = head->Next;
        head->Next = newNode;
        
        return L;
    }
    while (tail != NULL)
    {
        if (tail == P)
        {
            PtrToLNode newNode = (List)malloc(sizeof(struct LNode));
            newNode->Data = X;
            newNode->Next = tail;
            head->Next = newNode;
            
            return L;
        }
        head = head->Next;
        tail = tail->Next;
    }
    printf("Wrong Position for Insertion\n");
    return ERROR;
}
List Delete(List L, Position P)
{
    if (P == NULL || L == NULL)
    {
        return ERROR;
    }
    PtrToLNode head = L;
    PtrToLNode tail = L->Next;
    if (L == P)
    {   
        return L->Next;
    }
    // 从第二个节点向后滑
    while (tail != NULL)
    {
        if (tail == P)
        {
            head->Next = tail->Next;
            tail = head->Next;
            return L;
        }
        head = head->Next;
        tail = tail->Next;
    }
    printf("Wrong Position for Deletion\n");
    return ERROR;
}

//简化思路
Position Find(List L, ElementType X)
{
    while (L != NULL)
    {
        if (L->Data == X)
        {
            return L;
        }
        L = L->Next;
    }
    return ERROR;
}
List Insert(List L, ElementType X, Position P)
{
    //题意是可以在空链表插入，也可以在末尾插入。
    //空链表插入或首位置插入
    if (P == L)
    {
        PtrToLNode newNode = (List)malloc(sizeof(struct LNode));
        newNode->Data = X;
        newNode->Next = L;
        L = newNode;
        return L;
    }
    PtrToLNode head = L;
    PtrToLNode tail = L->Next;
    //其他节点插入
    //这里比较的是tail,为了确保tail可以指到末尾,使用head做判断。在末尾插入时NULL==NULL
    while (head != NULL)
    {
        if (tail == P)
        {
            PtrToLNode newNode = (List)malloc(sizeof(struct LNode));
            newNode->Data = X;
            newNode->Next = tail;
            head->Next = newNode;   
            return L;
        }
        head = head->Next;
        // 避免段错误
        if(head!=NULL){
            tail = tail->Next;
        }
    }
    printf("Wrong Position for Insertion\n");
    return ERROR;
}
List Delete(List L, Position P)
{
    //空链表错误
    if (L == NULL)
    {
        return ERROR;
    }
    
    //首节点删除
    if (L == P)
    {   
        return L->Next;
    }

    //其他节点删除    
    PtrToLNode head = L;
    PtrToLNode tail = L->Next;
    while (tail != NULL)
    {
        if (tail == P)
        {
            head->Next = tail->Next;
            tail = head->Next;
            return L;
        }
        head = head->Next;
        tail = tail->Next;
    }
    printf("Wrong Position for Deletion\n");
    return ERROR;
}