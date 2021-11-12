#include <stdio.h>
#include <time.h>
int vector[8][2]=
        {
                1,2,
                -1,-2,
                -2,1,
                2,1,
                2,-1,
                1,-2,
                -1,2,
                -2,-1
        };//控制方向

int count=0;//统计步数
int recursion=0;//统计递归次数

void greedy(int x,int y,int room[][8],int* toward)//贪心算法，计算走下一步后，可走的方案，以升序排序
{
    int point[8]={0};//统计下一步不同时，各自再行动的可行方案

    for (int i=0;i<8;i++)//统计部分
    {
        int x_=x,y_=y;
        x_+=vector[i][0];
        y_+=vector[i][1];
        if (0<=x_ && x_<=7 && 0<=y_ && y_<=7 && room[x_][y_]==0)
        {

            for (int j=0;j<8;j++)
            {
                int x__=x_,y__=y_;
                x__+=vector[j][0];y__+=vector[j][1];
                if (0<=x__ && x__<=7 && 0<=y__ && y__<=7 && room[x__][y__]==0) point[i]++;
            }
        }
    }
    int k=0;

    while (1)//排序部分，采用选择排序
    {
        int min=9,min_i=-1;
        for (int i=0;i<8;i++)
        {
            if ( point[i]<min)
            {
                min=point[i];
                min_i=i;
            }
        }
        if (min==9) break;
        toward[k]=min_i;
        point[min_i]=9;
        k++;
    }

}

void move(int x, int y,int room[][8])//行动
{
    int i=0;
    count++;//增加步数
    recursion++;//增加函数调用次数
    room[x][y]=count;//填入走到这一格时的步数

    int toward[8]={0};//储存排好序后的方向
    greedy(x,y,room,toward);
    while (count<64 && i<8)
    {
        int x_=x+vector[toward[i]][0],y_=y+vector[toward[i]][1];
        if (0<=x_ && x_<=7 && 0<=y_ && y_<=7 && room[x_][y_]==0)
            move(x_,y_,room);
        i++;
    }
    if (count <64)//表明之前行动方案行不通，退一步。
    {
        count --;
        room[x][y]=0;
    }

}

void print(int room[][8])//打印落步顺序
{
    printf("跳跃顺序如下：\n");
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++) printf("%4d",room[i][j]);
        printf("\n");
    }


}


int main()//主函数
{

    int room[8][8]={0};
    int x,y;
    clock_t start,finish;
    double duration;  //运行用时
    printf("该程序为马踏棋盘，棋盘大小为8*8\n横纵坐标范围皆为[0,7]，横纵坐标输入以空格分离\n请输入起始位置：");
    scanf("%d%d",&x,&y);
    start = clock();

    move(x,y,room);
    print(room);

    finish = clock();
    duration = (double) (finish - start) / CLOCKS_PER_SEC;
    printf("运行用时: %f second\n", duration);
    printf("递归次数：%d\n",recursion);
    return 0;

}