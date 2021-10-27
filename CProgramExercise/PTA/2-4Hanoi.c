#include<stdio.h>

/**
 * 移动操作
 * @param n 第一个架子的盘子数
 * @param x 第一个架子
 * @param y 第二个架子
 * @param z 第三个架子
 */
void move(int n, char x, char y, char z);

int main() {
    //A、B、C分别代表三个柱子
    char ch1 = 'A';
    char ch2 = 'B';
    char ch3 = 'C';
    //n代表圆盘的个数
    int n;
    scanf("%d", &n);
    move(n, ch1, ch2, ch3);
    return 0;
}
//
void move(int n, char x, char y, char z) {
    if (n == 1)
        printf("%c->%c\n", x, z);
    else {
        move(n - 1, x, z, y);
        printf("%c->%c\n", x, z);
        move(n - 1, y, x, z);
    }
}
 