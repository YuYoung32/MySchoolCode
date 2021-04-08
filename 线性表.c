//顺序表函数
void ListEmpty(L);
void ListLength(L);
void GetElem(L, i, &e);
void LocateElem(L, e, compare());
void ListInsert($L, i, e);
void ListDelete(&L, i, &e);

//A并B计入A中
void union(list &A, list B)
{
    Len_A = ListLength(A);
    Len_B = ListLength(B);
    for(i = 1; i <= Len_B; i++)
    {
        GetElem(B, i, &e)
        if(LocateElem(A, e, equal) = 0)
            ListInsert(&A, ++Len_A, e)
    }

}

//A交B计入A中
void intersection(list &A, list B)
{
    Len_A = ListLength(A);
    Len_B = ListLength(B);
    for(i = 1; i <= Len_B; i++)
    {
        GetElem(B, i, &e);
        for(j = 1; j <= Len_A; )
        {
            GetElem(A, j, &r);
            j++;
            if( e != r)
            {
                ListDelete(&A, j, r);
                Len_A--;
            }

        }

    }
}

//A交B计入C中
void intersection(list A, list B, list &C)
{
    InitList(C);
    Len_B = ListLength(B);
    for(i = 1, j = 1; i <= Len_B)
    {
        GetElem(B, i, &e);
        if(LocateElem(A, e, equal) != 0)
            ListInsert(&C, j++, e);
    }
}

//AB有序（不递减），合并两者，使之仍有序，储存于C中
void merge(list A, list B, list C)
{
    InitList(C);
    i = 1;
    j = 1;
    k = 0;
    Len_A = ListLength(A);
    Len_B = ListLength(B);
    while(i <= Len_A && j <= Len_B)
    {
        GetElem(A, i, &e);
        GetElem(B, j, &r);
        if(e <= r)
        {
            ListInsert(&C, ++k, e);
            i++;
        }

        else
        {
            ListInsert(&C, ++k, r);
            j++;
        }

    }
    while(i <= Len_A)
    {
        GetElem(A, i, &e);
        ListInsert(&C, ++k, e);
        i++;
    }

    while(j <= Len_B)
    {
        GetElem(A, j, &r);
        ListInsert(&C, ++k, r);
        j++;
    }

}

//集合运算（A-B）∪（B - A）
Status function(List &A,List &B){
    ALength = ListLength(A);
    BLength = ListLength(B);
    for(i = 0; i < ALength; i ++){
        GetElem(A, i, e);
        k = j = LocateElem(B, e, =);
        while(j){                                       //删除B中与A相同元素
            ListDelete(B, j, et);
            j = LocateElem(B, e, =);
            BLength --;
        }
        if(k){
            while(k){
                ListDelete(A, k, et);          //B中存在，删除A中相同元素
                k = LocateElem(A, e, =);
                ALength --;
            }
            i --;                                   //i位置保持不变
        }
    }
    for(i = 0; i < BLength; i ++){
        GetElem(B, i, e);
        ListInsert(A, ALength ++, e);
    }
    ALength --;
    return OK;
}

/*
要使循环队列不损失一个空间全部都能得到利用，
可设置一个front指示队头位置和一个length表示队列长度（不设rear），
请编写与此结构相应的队列初始化、入队与出队算法。
*/
Status InitQueue_Cir(Queue &Q){
    Q.front = Q.base = (QElemType *)malloc(MAXSIZE * sizeof(QElemType));
    if(!Q.base)
        exit(OVERFLOW);
    Q.length = 0;
}

Status EnQueue(Queue &Q, QElemType e){
    if(Q.length == MAXSIZE - 1)
        return ERROR;//已满
    Q.base[Q.front] = e;
    Q.front = (Q.front + 1) % MAXSIZE;
    Q.length ++;
}

Status DeQueue(Queue &Q, QElemType e){
    if(!Q.length)
        return ERROR;//已空
    e = Q.base[(Q.front - Q.length + MAXSZIE) % MAXSZIE];
    Q.front = (Q.front - 1 + MAXSIZE) % MAXSIZE;
}















