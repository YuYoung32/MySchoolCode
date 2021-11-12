#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <time.h>


int Partition(int num[], int start, int end) {
    //以第一个为中轴点，记录中轴点信息
    int key = num[start];
    //每一轮循环代表一趟，最后key前比num[key]小，后比num[key]大
    while (start < end) {
        //在后半部分找小的，放过大的 这里start不需要等于end因为方便后面赋值
        while (start < end && num[end] >= key) {
            end--;
        }
        num[start] = num[end];
        //前半部分找大的，放过小的
        while (start < end && num[start] <= key) {
            start++;
        }
        num[end] = num[start];
    }
    //中间的位置赋值
    num[start] = key;
    //返回中间的位置

    return start;
}

void QuickSort(int num[], int start, int end) {
    if (start < end) {
        //分割
        int key = Partition(num, start, end);
        //前半部分和后半部分进行quicksort，最中间不要管
        QuickSort(num, start, key - 1);
        QuickSort(num, key + 1, end);
    }
}


bool Check(const int num[], int n) {
    int i;
    for (i = 1; i < n; ++i) {
        if (num[i] >= num[i - 1]) {
            continue;
        } else {
            return false;
        }
    }
    if (i == n) {
        return true;
    }
    return false;
}

int *Generate(int n) {
    int *num = (int *) malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        num[i] = rand() * rand() % n;
    }
    return num;
}

int main() {
    float begin, end;
    int amount = ;
    int *num = Generate(amount);
    begin = clock();
    //放入测试函数
    QuickSort(num, 0, amount - 1);
    //******
    end = clock();
    printf("total time cost is %5.2f ms\n", end - begin);

    if (Check(num, amount)) {
        printf("result is right\n\n");
    } else {
        printf("result is wrong\n\n");
    }
    free(num);
    return 0;
}