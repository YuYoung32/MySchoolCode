//顺序栈初始化
Status InitStack(SqStack &S){
    S.base = (SElemType * )malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S.base)
        exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}
//链栈初始化
Status InitStack(LStack &S){
    S -> base = NULL;
    S -> top = S -> base;
    S -> stacksize = 0;
}

//Push
Status Push(SqStack S, SElemType &e){
//插入元素e为新栈顶元素
    if(S.top – S.base >= S.stacksize){
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
//若栈不空删除栈顶元素，e返回其值
    if(S.top == S.base)//栈空
        return ERROR
    e = * --p;
return OK;
}

//GetTop
Status GetTop(SqStack S, SElemType &e){
//用e返回栈顶元素
    if(S.top == S.base)
        e = *(S.top -1); //取前一个位置但S.top自身没变
return OK;
}

//数制转换10 -> 2
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

//迷宫算法
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


