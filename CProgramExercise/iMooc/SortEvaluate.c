//编写与评价各种排序算法的时间
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/**
 * 检测递增排序正确性，用后面一个大于等于前面一个进行判断
 * @param num 数组
 * @param n 元素个数
 */
bool Check(const int num[], int n);

/**
 * 生成随机的数量为n的随机int数组
 * @param n
 * @return 随机int数组
 */
int *Generate(int n);

/**
 * 冒泡排序
 * @param num 数组
 * @param n 元素个数
 */
void BubbleSort(int num[], int n);

/**
 * 选择排序
 * @param num 数组
 * @param n 元素个数
 */
void SelectSort(int num[], int n);

/**
 * 插入排序
 * @param num 数组
 * @param n 元素个数
 */
void InsertSort(int num[], int n);

/**
 * 归并排序
 * @param num 数组
 * @param start 开始的索引 一开始是0
 * @param end 结束的索引 元素个数减1
 */
void MergeSort(int num[], int start, int end);

/**
 * 快速排序
 * @param num 数组
 * @param start 开始的索引 一开始是0
 * @param end 结束的索引 元素个数减1
 */
void QuickSort(int num[], int start, int end);

/**
 * 测试排序函数运行时间与正确性
 * @param num 数组
 * @param amount 数组元素个数
 */
void TestAllSortFunction(const int num[], int amount);

int main() {
    int *num, amount;
    double begin, end;
    //数组检验排序正确性与时间
    printf("||||||||||||||||||||||below are totally random|||||||||||||||||||||||||||||||");
    for (int i = 0; i < 5; ++i) {
        amount = (int) pow(10, (i + 2));
        if (amount % 10 != 0) {
            amount++;
        }
        printf("-------------------------amount: %d ----------------------------\n", amount);
        num = Generate(amount);
        TestAllSortFunction(num, amount);
        free(num);
    }
    printf("||||||||||||||||||||||below are lifhtly random|||||||||||||||||||||||||||||||");
    for (int i = 0; i < 5; ++i) {
        amount = (int) pow(10, (i + 2));
        if (amount % 10 != 0) {
            amount++;
        }
        printf("-------------------------amount: %d ----------------------------\n", amount);
        num = Generate(amount);
        //进行稍微的无序
        QuickSort(num,0,amount-1);
        num[amount/2]=num[0];

        TestAllSortFunction(num, amount);
        free(num);
    }
    return 0;
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

void BubbleSort(int num[], int n) {
    int temp;
    //对于n-1个数判断
    for (int i = 0; i < n - 1; ++i) {
        //每一遍流程后最后一个都是最大的
        //判断过的不用判断，因为是实时交换所以最后一个判断不到
        for (int j = 0; j < n - 1 - i; ++j) {
            if (num[j] > num[j + 1]) {
                temp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = temp;
            }
        }
    }
}

void SelectSort(int num[], int n) {
    int maxIndex, temp;
    //对于n-1个数判断
    for (int i = 0; i < n - 1; ++i) {
        //这里要等于0，每次都从第一个开始
        maxIndex = 0;
        //每次找到最大的放在最后面，需要第一次需要判断最后一个
        for (int j = 0; j < n - i; ++j) {
            if (num[j] > num[maxIndex]) {
                maxIndex = j;
            }
        }
        temp = num[maxIndex];
        num[maxIndex] = num[n - i - 1];
        num[n - i - 1] = temp;
    }
}

void InsertSort(int num[], int n) {
    //假设第一个是已经排序好的数组，后面如果有存在比 已经排序好的最后一个元素 小的就向遍历并向后移动
    //直到遇到比当前小的，因为后面的已经向后移动，所以在当前位置之间写入
    int temp, i, j;
    //从1开始
    for (i = 1; i < n; ++i) {
        if (num[i] >= num[i - 1]) {
            continue;
        } else {//发现小的，进行查找与移位
            //后面要移位覆盖它，所以记录变量
            temp = num[i];
            //从i-1开始因为要找到下一个比当前位置小的数
            for (j = i - 1; j >= 0 && num[j] >= temp; --j) {
                num[j + 1] = num[j];
            }
            //当前位置比temp小，所以下一个位置置数。或者全部都符合条件，则放到首位置
            num[j + 1] = temp;
        }
    }
}

void Merge(int num[], int start, int mid, int end) {
    int start1 = start, start2 = mid + 1;
    //创建合适大小的数组，在原数组外选择并入，然后把这个数组赋值给原数组
    int total = end - start + 1;
    int tempNum[total];
    //进行新数组的赋值
    for (int j = 0; j < total; j++) {
        //前半部分到头
        if (start1 > mid) {
            for (; start2 <= end; start2++) {
                tempNum[j++] = num[start2];
            }
            break;
        }
        //后半部分到头
        if (start2 > end) {
            for (; start1 <= mid; start1++) {
                tempNum[j++] = num[start1];
            }
            break;
        }
        //正常判断与赋值新数组，把小的放前面
        if (num[start1] <= num[start2]) {
            tempNum[j] = num[start1];
            start1++;
        } else {
            tempNum[j] = num[start2];
            start2++;
        }
    }
    //迁移回老数组
    for (int i = start, j = 0; j < total; ++i, ++j) {
        num[i] = tempNum[j];
    }
}

void MergeSort(int num[], int start, int end) {
    int mid;
    if (start < end) {
        mid = (start + end) / 2;
        MergeSort(num, start, mid);
        MergeSort(num, mid + 1, end);
        Merge(num, start, mid, end);
    }
}

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

void TestAllSortFunction(const int constNum[], int amount) {
    char *funcName[] = {"BubbleSort", "SelectSort", "InsertSort", "MergeSort", "QuickSort"};
    double begin, end;
    for (int i = 4; i >= 0; --i) {
        //不改变原来的，要不然后面没法排了
        int *num = (int *) malloc(amount * sizeof(int));
        for (int j = 0; j < amount; ++j) {
            num[j] = constNum[j];
        }

        begin = clock();
        switch (i) {
            case 0:
                BubbleSort(num, amount);
                break;
            case 1:
                SelectSort(num, amount);
                break;
            case 2:
                InsertSort(num, amount);
                break;
            case 3:
                //递归深度过深 栈溢出 不要再运行了 如果电脑好可以注释掉这个if
                if(amount>200000){
                    printf("may time out, exit\n\n");
                    return;}
                MergeSort(num, 0, amount - 1);
                break;
            case 4:
                QuickSort(num, 0, amount - 1);
                break;;
            default:
                break;
        }
        end = clock();

        printf("when the amount is %d, time cost of %s is %5.2f ms\n", amount, funcName[i], end - begin);
        if (Check(num, amount)) {
            printf("result is right\n\n");
        } else {
            printf("!!!result is wrong!!!\n\n");
        }
        free(num);
    }

}













