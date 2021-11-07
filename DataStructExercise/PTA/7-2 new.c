#include <stdio.h>
#include <stdlib.h>

#define N 10000

int main() {
    int num1[N] = {0};
    int num2[N] = {0};
    int add[N] = {0};
    int multi[N] = {0};
    int n, con, index;
    scanf("%d", &n);
    while (n--) {
        scanf("%d %d", &con, &index);
        num1[index] += con;

    }
    scanf("%d", &n);
    while (n--) {
        scanf("%d %d", &con, &index);
        num2[index] += con;
    }
    //乘法
    for (int i = 0; i < N - 1; ++i) {
        if (num1[i]) {
            for (int j = 0; j < N - 1; ++j) {
                if (num2[j]) {
                    multi[i + j] += num1[i] * num2[j];
                }
            }
        }
    }

    int cnt = 0;
    for (int i = N - 1; i >= 0; --i) {
        if (multi[i]) {
            if (cnt++) {
                printf(" ");
            }
            printf("%d %d", multi[i], i);
        }
    }
    if (cnt == 0) {
        printf("0 0");
    }
    printf("\n");


    //加法
    for (int i = 0; i < N - 1; ++i) {
        if (num1[i] && num2[i]) {
            add[i] += num1[i] + num2[i];
            continue;
        }
        if (num1[i]) {
            add[i] += num1[i];
            continue;
        }
        if (num2[i]) {
            add[i] += num2[i];
            continue;
        }
    }
    cnt = 0;
    for (int i = N - 1; i >= 0; --i) {
        if (add[i]) {
            if (cnt++) {
                printf(" ");
            }
            printf("%d %d", add[i], i);
        }
    }
    //特殊情况
    if (cnt==0) {
        printf("0 0");
    }

    return 0;
}