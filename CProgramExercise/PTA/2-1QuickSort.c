#include <stdio.h>

/**
 * 枢轴值为第一个数，进行一次分离，位置前半部分都不大于枢轴值，后面都不小于
 * @param num 需要比较的数组
 * @param low 低位置
 * @param high 高位置
 * @return 最后枢轴的位置
 */
int Partition(int num[], int low, int high);

/**
 * @param num 需要比较的数组
 * @param low 起始位置
 * @param high 最后位置
 */
void QuickSort(int num[], int low, int high);


int main() {
    int num[10000];
    //0为枢轴量，不填入
    int i = 1;
    while (scanf("%d", &num[i]) != EOF) {
        i++;
    }
    --i;
    QuickSort(num, 1, i);
    printf("%d,",num[1]);
    printf("%d",num[i]);
    return 0;
}

int Partition(int num[], int low, int high) {
    //枢轴值记录，以第一个值为枢轴值
    num[0] = num[low];
    while (low < high) {
        //空位在前，找小
        while (low < high && num[high] >= num[0]) {
            high--;
        }
        num[low] = num[high];
        //空位在后，找大
        while (low < high && num[low] <= num[0]) {
            low++;
        }
        num[high] = num[low];

    }
    //low==high
    num[low] = num[0];
    return low;
}

void QuickSort(int num[], int low, int high) {
    //需判定条件，因为Partition(...)并没有改变low和high
    if (low < high) {
        int keyPosition = Partition(num, low, high);
        QuickSort(num, low, keyPosition - 1);
        QuickSort(num, keyPosition + 1, high);
    }
}