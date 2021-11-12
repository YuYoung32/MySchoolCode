#include <stdio.h>
#include <malloc.h>

#define M 6
#define N 6
#define END N-2
int flag = 0;
typedef struct {
    int x, y, d;
} position;

/*创建迷宫*/
void creat_maze(int a[][M]) {
    int i, j;
    for (i = 0; i <= N - 1; i++)
        for (j = 0; j <= M - 1; j++)
            scanf("%1d", &a[i][j]);
}

position nextq(int maze[][M], position q) {
    if (q.d == 0)
        q.y++;
    else if (q.d == 1)
        q.x++;
    else if (q.d == 2)
        q.y--;
    else if (q.d == 3)
        q.x--;
    return q;
}

void initialmat(int route[][M])       //初始化输出路径图
{
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            route[i][j] = 1;
}

void print_maze(int mat[][M])        //输出迷宫
{
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }

}

void MazePath(int maze[][M], int route[][M], position ps) {
    position q;
    route[ps.x][ps.y] = 0;
    maze[ps.x][ps.y] = -1;
    q = nextq(maze, ps);
    q.d = 0;
    if (q.x == END && q.y == END) {
        flag++;
        printf("\n第%d条路:\n", flag);
        route[END][END] = 0;
        print_maze(route);
        route[END][END] = 1;
    } else if (maze[q.x][q.y] == 0)
        MazePath(maze, route, q);
    if (ps.d <= 3) {
        ps.d++;
        MazePath(maze, route, ps);
    }
    route[ps.x][ps.y] = 1;
    maze[ps.x][ps.y] = 0;
}

void main() {
    int maze[N][M], route[N][M];
    position ps;
    ps.x = ps.y = 1;
    ps.d = 0;
    printf("输入一个迷宫(%d*%d):\n", N, M);
    creat_maze(maze);
    printf("\n输出该迷宫:\n");
    print_maze(maze);
    printf("输出从(1,1)到(%d,%d)的所有通路:\n", N - 2, M - 2);
    initialmat(route);
    MazePath(maze, route, ps);
}