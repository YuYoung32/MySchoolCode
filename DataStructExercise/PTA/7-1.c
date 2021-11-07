#include <stdio.h>

/**
 * 数组左移n位
 * @param num 数组
 * @param gap 位数
 * @param n 数组元素数量
 */
void Move(int num[], int gap, int n);

int main() {
    int n, gap;
    scanf("%d %d", &n, &gap);
    int num[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%d", &num[i]);
    }
    Move(num, gap, n);
    for (i = 0; i < n - 1; ++i) {
        printf("%d ", num[i]);
    }
    printf("%d", num[i]);
}

void Move(int num[], int gap, int n) {
    int j;
    for (int i = 0; i < gap; ++i) {
        //一次移动
        int temp = num[0];
        for (j = 0; j < n - 1; ++j) {
            num[j] = num[j + 1];
        }
        num[j] = temp;
    }
}