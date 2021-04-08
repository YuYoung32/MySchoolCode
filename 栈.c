//˳��ջ��ʼ��
Status InitStack(SqStack &S){
    S.base = (SElemType * )malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S.base)
        exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}
//��ջ��ʼ��
Status InitStack(LStack &S){
    S -> base = NULL;
    S -> top = S -> base;
    S -> stacksize = 0;
}

//Push
Status Push(SqStack S, SElemType &e){
//����Ԫ��eΪ��ջ��Ԫ��
    if(S.top �C S.base >= S.stacksize){
        S.base = (SElemType * )realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if(!S.base)
            exit(OVERFLOW);
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top ++= e;
}

//Pop
Status Pop(SqStack S, SElemType &e){
//��ջ����ɾ��ջ��Ԫ�أ�e������ֵ
    if(S.top == S.base)//ջ��
        return ERROR
    e = * --p;
return OK;
}

//GetTop
Status GetTop(SqStack S, SElemType &e){
//��e����ջ��Ԫ��
    if(S.top == S.base)
        e = *(S.top -1); //ȡǰһ��λ�õ�S.top����û��
return OK;
}

//����ת��10 -> 2
 void conversion(){
    InitStack(S);
    scanf("%d", N);
    while(N){
        Push(S, N%2);
        N /= 2;
    }
    while(!StackEmpty(S)){
        pop(S, e);
        printf("%d",e)
    }
 }

//�Թ��㷨
typedef strcut
{
    int ord;
    PosType seat;
    int di
} SElemType;

Status MazePath(MazeType maze, PosType start, PosType end)
{
    InintStack(S);
    curpos = start;
    curstep = 1;
    do
    {
        if (Pass(curpos))
        {
            Footprint(curpos);
            e = (curstep, curpos, 1);
            Push(S, e);
            if (curpos == end)
                return(TRUE);
            curpos = NextPos(curpos, 1);
            curstep ++;
        }
        else
        {
            if(!StackEmpty(S))
            {
                Pop(S,e);
                while(e.di == 4 && !StackEmpty(S))
                {
                    MarkPrint(e, seat);
                    Pop(S, e);
                }

                if(e.di < 4)
                {
                    e.di ++;
                    Push(S, e);
                    curpos = NextPos(e.seat, e.di);
                }
            }
        }
    }
    while(!StackEmpty(S));
    return(FALSE);
}


