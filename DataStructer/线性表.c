//˳�����
void ListEmpty(L);
void ListLength(L);
void GetElem(L, i, &e);
void LocateElem(L, e, compare());
void ListInsert($L, i, e);
void ListDelete(&L, i, &e);

//A��B����A��
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

//A��B����A��
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

//A��B����C��
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

//AB���򣨲��ݼ������ϲ����ߣ�ʹ֮�����򣬴�����C��
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

//�������㣨A-B���ȣ�B - A��
Status function(List &A,List &B){
    ALength = ListLength(A);
    BLength = ListLength(B);
    for(i = 0; i < ALength; i ++){
        GetElem(A, i, e);
        k = j = LocateElem(B, e, =);
        while(j){                                       //ɾ��B����A��ͬԪ��
            ListDelete(B, j, et);
            j = LocateElem(B, e, =);
            BLength --;
        }
        if(k){
            while(k){
                ListDelete(A, k, et);          //B�д��ڣ�ɾ��A����ͬԪ��
                k = LocateElem(A, e, =);
                ALength --;
            }
            i --;                                   //iλ�ñ��ֲ���
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
Ҫʹѭ�����в���ʧһ���ռ�ȫ�����ܵõ����ã�
������һ��frontָʾ��ͷλ�ú�һ��length��ʾ���г��ȣ�����rear����
���д��˽ṹ��Ӧ�Ķ��г�ʼ�������������㷨��
*/
Status InitQueue_Cir(Queue &Q){
    Q.front = Q.base = (QElemType *)malloc(MAXSIZE * sizeof(QElemType));
    if(!Q.base)
        exit(OVERFLOW);
    Q.length = 0;
}

Status EnQueue(Queue &Q, QElemType e){
    if(Q.length == MAXSIZE - 1)
        return ERROR;//����
    Q.base[Q.front] = e;
    Q.front = (Q.front + 1) % MAXSIZE;
    Q.length ++;
}

Status DeQueue(Queue &Q, QElemType e){
    if(!Q.length)
        return ERROR;//�ѿ�
    e = Q.base[(Q.front - Q.length + MAXSZIE) % MAXSZIE];
    Q.front = (Q.front - 1 + MAXSIZE) % MAXSIZE;
}















