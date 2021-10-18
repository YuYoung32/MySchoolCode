#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode List;
int Length( List L );

// 已通过
int Length( List L ){
    int cnt=0;
    while (L!=NULL)
    {
        L=L->Next;
        cnt++;
    }
    return cnt;
}