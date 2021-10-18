#include <stdio.h>
#include <stdlib.h>

#define ERROR NULL
typedef enum {false, true} bool;
typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

List MakeEmpty(); 
Position Find( List L, ElementType X );
bool Insert( List L, ElementType X, Position P );
bool Delete( List L, Position P );

//已通过
List MakeEmpty(){
    PtrToLNode head = (List)malloc(sizeof(struct LNode));
    head->Data=-1;
    head->Next=NULL;
    return head;
}

Position Find(List L, ElementType X)
{
    //跳过头节点
    L=L->Next;
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

bool Insert(List L, ElementType X, Position P)
{
    PtrToLNode head = L;
    PtrToLNode tail = L->Next;
    while (head!=NULL)
    {
        if(tail==P){
            PtrToLNode newNode = (List)malloc(sizeof(struct LNode));
            newNode->Data=X;
            newNode->Next=tail;
            head->Next=newNode;
            return true;
        }
        head=head->Next;
        if(head!=NULL){
            tail=tail->Next;
        }
    }
    printf("Wrong Position for Insertion\n");
    return false;
}

bool Delete(List L, Position P)
{
    PtrToLNode head = L;
    PtrToLNode tail = L->Next;
    while (tail!=NULL)
    {
        if(tail==P){
            head->Next=tail->Next;
            free(P);
            return true;
        }
        head=head->Next;
        tail=tail->Next;
    }
    printf("Wrong Position for Deletion\n");
    return false;
}