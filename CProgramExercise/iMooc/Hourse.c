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
        };//���Ʒ���

int count=0;//ͳ�Ʋ���
int recursion=0;//ͳ�Ƶݹ����

void greedy(int x,int y,int room[][8],int* toward)//̰���㷨����������һ���󣬿��ߵķ���������������
{
    int point[8]={0};//ͳ����һ����ͬʱ���������ж��Ŀ��з���

    for (int i=0;i<8;i++)//ͳ�Ʋ���
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

    while (1)//���򲿷֣�����ѡ������
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

void move(int x, int y,int room[][8])//�ж�
{
    int i=0;
    count++;//���Ӳ���
    recursion++;//���Ӻ������ô���
    room[x][y]=count;//�����ߵ���һ��ʱ�Ĳ���

    int toward[8]={0};//�����ź����ķ���
    greedy(x,y,room,toward);
    while (count<64 && i<8)
    {
        int x_=x+vector[toward[i]][0],y_=y+vector[toward[i]][1];
        if (0<=x_ && x_<=7 && 0<=y_ && y_<=7 && room[x_][y_]==0)
            move(x_,y_,room);
        i++;
    }
    if (count <64)//����֮ǰ�ж������в�ͨ����һ����
    {
        count --;
        room[x][y]=0;
    }

}

void print(int room[][8])//��ӡ�䲽˳��
{
    printf("��Ծ˳�����£�\n");
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++) printf("%4d",room[i][j]);
        printf("\n");
    }


}


int main()//������
{

    int room[8][8]={0};
    int x,y;
    clock_t start,finish;
    double duration;  //������ʱ
    printf("�ó���Ϊ��̤���̣����̴�СΪ8*8\n�������귶Χ��Ϊ[0,7]���������������Կո����\n��������ʼλ�ã�");
    scanf("%d%d",&x,&y);
    start = clock();

    move(x,y,room);
    print(room);

    finish = clock();
    duration = (double) (finish - start) / CLOCKS_PER_SEC;
    printf("������ʱ: %f second\n", duration);
    printf("�ݹ������%d\n",recursion);
    return 0;

}