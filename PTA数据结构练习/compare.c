#include <stdio.h>
#include <stdlib.h>

#define ERROR 1e8
typedef int ElementType;
typedef enum
{
    push,
    pop,
    end
} Operation;
typedef enum
{
    false,
    true
} bool;
typedef int Position;
struct SNode
{
    ElementType *Data;
    Position Top1, Top2;
    int MaxSize;
};
typedef struct SNode *Stack;

Stack CreateStack(int MaxSize);
bool Push(Stack S, ElementType X, int Tag);
ElementType Pop(Stack S, int Tag);

Stack CreateStack(int MaxSize)
{
    Stack stack = (Stack)malloc(sizeof(Stack));
    stack->Data = (ElementType *)malloc(sizeof(ElementType) * MaxSize);
    stack->Top1 = -1;
    stack->Top2 = MaxSize;
    stack->MaxSize = MaxSize;
    return stack;
}
bool Push(Stack S, ElementType X, int Tag)
{
    if (S == NULL)
        return false;
    if (S->Top1 + 1 == S->Top2)
    {
        printf("Stack Full\n");
        return false;
    }
    if (Tag == 1)
        S->Data[++S->Top1] = X;
    else
        S->Data[--S->Top2] = X;
    return true;
}
ElementType Pop(Stack S, int Tag)
{
    if (S == NULL)
        return ERROR;
    if (Tag == 1)
    {
        if (S->Top1 == -1)
        {
            printf("Stack 1 Empty\n");
            return ERROR;
        }
        return S->Data[S->Top1--];
    }
    else
    {
        if (S->Top2 == S->MaxSize)
        {
            printf("Stack 2 Empty\n");
            return ERROR;
        }
        return S->Data[S->Top2++];
    }
}