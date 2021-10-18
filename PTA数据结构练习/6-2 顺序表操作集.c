#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5
#define ERROR -1
typedef enum
{
    false,
    true
} bool;
typedef int ElementType;
typedef int Position;
typedef struct LNode *List;
struct LNode
{
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List MakeEmpty();
Position Find(List L, ElementType X);
bool Insert(List L, ElementType X, Position P);
bool Delete(List L, Position P);

//题解，已通过
List MakeEmpty()
{
    List p;
    p = (List)malloc(sizeof(struct LNode));
    p->Last = -1; //注意这里的初始位置，若为0，则表示初始位置的下一个
    return p;
}

Position Find(List L, ElementType X)
{
    Position i = 0;
    for (i = 0; i <= L->Last; i++)
    {
        if (L->Data[i] == X)
        {
            return i;
        }
    }
    return ERROR;
}

bool Insert(List L, ElementType X, Position P)
{
    if (L->Last >= MAXSIZE - 1)
    {
        printf("FULL");
        return false;
    }
    if (P < 0 || P > L->Last + 1)
    {
        printf("ILLEGAL POSITION");
        return false;
    }

    Position i;
    //注意这里的插入方法，可以插入在末尾位置的下一个
    for (i = L->Last + 1; i > P; i--)
    {
        L->Data[i] = L->Data[i - 1];
    }
    L->Data[P] = X;

    L->Last++;

    return true;
}

bool Delete(List L, Position P)
{
    if (P < 0 || P > L->Last)
    {
        printf("POSITION %d EMPTY", P);
        return false;
    }

    Position i;
    for (i = P; i < L->Last; i++)
    {
        L->Data[i] = L->Data[i + 1];
    }
    L->Last--;

    return true;
}
