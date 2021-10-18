#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode List;

ElementType FindKth( List L, int K );

// 已通过
ElementType FindKth( List L, int K ){
    int cnt=0;
    while (L!=NULL)
    {
        cnt++;
        if(cnt==K){
            return L->Data;
        }
        L=L->Next;
    }
    return ERROR;
    
}