#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    positive, negative
} Symbol;
typedef struct Digit *PtrToDigit;
struct Digit {
    int num;
    PtrToDigit before;
    PtrToDigit next;
};

/**
 * 以数字创建节点，前后节点置空
 * @param num 数字
 * @return 包装好的节点
 */
PtrToDigit CreateDigitNode(int num);

/**
 * 以一个含符号（正数：无前缀，负数：前缀“-”）字符串创建双向链表
 * @param flag 正负符号
 * @param str 字符串
 * @return 一个无头节点双向链表
 */
PtrToDigit CreateDigitList(Symbol *flag, char *str);

/**
 * 大数无符号相加
 * @param num1 大数链表
 * @param num2 大数链表
 * @return 相加后的和的双向链表
 */
PtrToDigit Add(PtrToDigit num1, PtrToDigit num2);

/**
 * 两个无符号数相减 num1 - num2
 * @param num1 减数链表
 * @param num2 被减数链表
 * @param resultFlag 结果符号
 * @return 结果链表
 */
PtrToDigit Sub(PtrToDigit num1, PtrToDigit num2, Symbol *resultFlag);

/**
 * 找到最后一个节点（大数的最低位）
 * @param list 大数中任意节点
 * @return 最后一个节点
 */
PtrToDigit FindEnd(PtrToDigit list);

/**
 * 获取链表长度
 * @param list 第一个节点
 * @return 长度（int）
 */
int GetListLength(PtrToDigit list);

/**
 * 打印链表，格式+-(+省略)num1num2num3...，全0只输出“0”
 * @param list 链表首结点
 */
void PrintList(PtrToDigit list, Symbol symbol);

/**
 * 释放整个链表
 * @param list
 */
void FreeList(PtrToDigit list);

/**
 * 比较两个相同长度的大数的大小
 * @param num1 大数链表
 * @param num2 大数链表
 * @return positive: num1>=num2; negative: num1<num2
 */
Symbol CompareList(PtrToDigit num1, PtrToDigit num2);

/**
 * 从一个链表复制出另一个链表
 * @param new 新链表
 * @return 新链表
 */
PtrToDigit DuplicateList(PtrToDigit origin);

/**
 * 无符号数乘法
 * @param num1 大数链表
 * @param num2 大数链表
 * @return 相乘后的大数链表
 */
PtrToDigit Multi(PtrToDigit num1, PtrToDigit num2);

/**
 * 一个无符号数乘以一个无符号大数
 * @param num 无符号数
 * @param numPtr 大数链表
 * @return 结果大数链表
 */
PtrToDigit SingleMulti(int num, PtrToDigit numPtr);

/**
 * 将一个大数乘以10^count次方，或者说向左移位，在后添0
 * @param count 多少个10
 * @param numPtr 大数链表
 * @return 移位后端的大数链表
 */
PtrToDigit Multi10(int count, PtrToDigit numPtr);

int main() {
    char strNum1[100], strNum2[100];
    //大数的双向链表
    PtrToDigit num1, num2, addResult, subResult, multiResult;

    //正负数标识
    Symbol flag1, flag2, addResultFlag, subResultFlag, multiResultFlag;

    scanf("%s", strNum1);
    scanf("%s", strNum2);

    num1 = CreateDigitList(&flag1, strNum1);
    num2 = CreateDigitList(&flag2, strNum2);

    //运算
    if (flag1 == positive && flag2 == positive) {
        addResult = Add(num1, num2);
        addResultFlag = positive;
        subResult = Sub(num1, num2, &subResultFlag);
        multiResult = Multi(num1, num2);
        multiResultFlag = positive;
    } else if (flag1 == negative && flag2 == negative) {
        addResult = Add(num1, num2);
        addResultFlag = negative;
        subResult = Sub(num2, num1, &subResultFlag);
        multiResult = Multi(num1, num2);
        multiResultFlag = positive;
    } else if (flag1 == positive && flag2 == negative) {
        addResult = Sub(num1, num2, &addResultFlag);
        subResult = Add(num1, num2);
        subResultFlag = positive;
        multiResult = Multi(num1, num2);
        multiResultFlag = negative;
    } else {//flag1==negative && flag2==positive
        subResult = Add(num1, num2);
        addResult = Sub(num2, num1, &addResultFlag);
        subResultFlag = negative;
        multiResult = Multi(num1, num2);
        multiResultFlag = negative;
    }

    //打印输出
    PrintList(addResult, addResultFlag);
    printf("\n");
    PrintList(subResult, subResultFlag);
    printf("\n");
    PrintList(multiResult, multiResultFlag);
    printf("\n");

    FreeList(num1);
    FreeList(num2);
    FreeList(addResult);
    FreeList(subResult);
    FreeList(multiResult);

    return 0;

}

PtrToDigit CreateDigitNode(int num) {
    PtrToDigit node = (PtrToDigit) malloc(sizeof(struct Digit));
    node->num = num;
    node->before = NULL;
    node->next = NULL;
    return node;
}

PtrToDigit CreateDigitList(Symbol *flag, char *str) {
    PtrToDigit head;
    PtrToDigit node;
    int i;
    //符号置位
    if (str[0] == '-') {
        *flag = negative;

        head = CreateDigitNode(str[1] - '0');
        i = 2;
    } else {
        *flag = positive;
        head = CreateDigitNode(str[0] - '0');
        i = 1;
    }
    PtrToDigit start = head;
    for (; i < strlen(str); ++i) {
        node = CreateDigitNode(str[i] - '0');
        //在节点末尾连接
        //正向连接
        start->next = node;
        //反向连接
        node->before = start;
        start = start->next;
    }
    return head;
}

PtrToDigit Add(PtrToDigit num1, PtrToDigit num2) {
    PtrToDigit longNum, shortNum;
    PtrToDigit longStart, shortStart;
    int sum, carry = 0;
    if (GetListLength(num1) >= GetListLength(num2)) {
        //不能使用原节点，因为以后还要用这个，所以原样复制一个
        longNum = DuplicateList(num1);
        shortNum = num2;
    } else {
        longNum = DuplicateList(num2);
        shortNum = num1;
    }
    longStart = FindEnd(longNum);
    shortStart = FindEnd(shortNum);
    while (longStart != NULL) {
        if (shortStart != NULL) {
            //本位
            sum = (longStart->num + shortStart->num + carry) % 10;
            //进位
            carry = (longStart->num + shortStart->num + carry) / 10;
            //更改已经计算过的便于输出
            longStart->num = sum;
            longStart = longStart->before;
            shortStart = shortStart->before;
        } else {
            //本位，超过shortNum部分设置为0且不为其迭代
            sum = (longStart->num + 0 + carry) % 10;
            //进位
            carry = (longStart->num + 0 + carry) / 10;
            longStart->num = sum;
            longStart = longStart->before;
        }
    }
    //如果最终有进位则表示在最高位进位，增加节点
    if (carry == 1) {
        PtrToDigit carryNode = CreateDigitNode(1);
        carryNode->next = longNum;
        longNum->before = carryNode;
        //移到头节点
        longNum = longNum->before;
    }
    return longNum;
}

PtrToDigit Sub(PtrToDigit num1, PtrToDigit num2, Symbol *resultFlag) {
    //使大数在前，小的在后面
    PtrToDigit big;
    PtrToDigit small;
    int sub, carry = 0;

    //从长度和相同长度下逐位比较大小
    if (GetListLength(num1) > GetListLength(num2)) {
        big = DuplicateList(num1);
        small = num2;
        *resultFlag = positive;
    } else if (GetListLength(num1) < GetListLength(num2)) {
        big = DuplicateList(num2);
        small = num1;
        *resultFlag = negative;
    } else {
        if (CompareList(num1, num2) == positive) {
            big = DuplicateList(num1);
            small = num2;
            *resultFlag = positive;
        } else {
            big = DuplicateList(num2);
            small = num1;
            *resultFlag = negative;
        }
    }

    PtrToDigit bigHead = FindEnd(big);
    PtrToDigit smallHead = FindEnd(small);

    //相减部分
    //有了上面的判断，下面减去的结果一定是正数，也就是说最高位没有借位
    while (bigHead != NULL) {
        if (smallHead != NULL) {
            //最高位没有借位
            if (bigHead->num - smallHead->num - carry >= 0) {
                sub = bigHead->num - smallHead->num - carry;
                carry = 0;
            } else {
                sub = 10 + bigHead->num - smallHead->num - carry;
                carry = 1;
            }
            bigHead->num = sub;
            bigHead = bigHead->before;
            smallHead = smallHead->before;
        } else {
            //smallHead已读取完
            if (bigHead->num - 0 - carry >= 0) {
                sub = bigHead->num - 0 - carry;
                carry = 0;
            } else {
                sub = 10 + bigHead->num - 0 - carry;
                carry = 1;
            }
            bigHead->num = sub;
            bigHead = bigHead->before;
        }
    }
    return big;
}

PtrToDigit FindEnd(PtrToDigit list) {
    while (list->next != NULL) {
        list = list->next;
    }
    return list;
}

int GetListLength(PtrToDigit list) {
    if (list == NULL) {
        return 0;
    }
    int cnt = 1;
    while (list->next != NULL) {
        cnt++;
        list = list->next;
    }
    return cnt;
}

void PrintList(PtrToDigit list, Symbol symbol) {
    if (list->num == 0) {
        printf("0");
        return;
    }
    if (symbol == negative) {
        printf("-");
    }
    while (list != NULL) {
        printf("%d", list->num);
        list = list->next;
    }
}

void FreeList(PtrToDigit list) {
    PtrToDigit temp;
    while (list != NULL) {
        temp = list->next;
        free(list);
        list = temp;
    }
}

Symbol CompareList(PtrToDigit num1, PtrToDigit num2) {
    while (num1 != NULL) {
        if (num1->num > num2->num) {
            return positive;
        } else if (num1->num < num2->num) {
            return negative;
        }
        //二者相等比较下一位
        num1 = num1->next;
        num2 = num2->next;
    }
    //全部相等
    return positive;
}

PtrToDigit DuplicateList(PtrToDigit origin) {
    PtrToDigit newNode = (PtrToDigit) malloc(sizeof(struct Digit));
    newNode->before = NULL;
    //头节点保存
    PtrToDigit newHead = newNode;
    while (origin != NULL) {
        newNode->num = origin->num;
        PtrToDigit temp = (PtrToDigit) malloc(sizeof(struct Digit));
        newNode->next = temp;
        temp->before = newNode;
        newNode = temp;
        origin = origin->next;
    }
    //尾节点置空
    newNode->before->next = NULL;
    free(newNode);
    return newHead;
}

PtrToDigit Multi(PtrToDigit num1, PtrToDigit num2) {
    //移位数
    int count = 0;
    //结果值与中间量
    PtrToDigit stepResult = CreateDigitNode(0), stepResultNew;
    //从最低位开始
    PtrToDigit start2 = FindEnd(num2);
    //使用竖式相乘
    //逐步使用start2乘start1
    while (start2 != NULL) {
        //中间量，进行一次相乘，并移位
        stepResultNew = SingleMulti(start2->num, num1);
        stepResultNew = Multi10(count, stepResultNew);
        stepResult = Add(stepResult, stepResultNew);
        count++;
        start2 = start2->before;
        free(stepResultNew);
    }
    return stepResult;
}

PtrToDigit SingleMulti(int num, PtrToDigit numPtr) {
    //创建新的从而不改变原来的
    numPtr = DuplicateList(numPtr);
    PtrToDigit start = FindEnd(numPtr);
    int local, carry = 0;
    while (start != NULL) {
        //本位
        local = (start->num * num + carry) % 10;
        //进位
        carry = (start->num * num + carry) / 10;
        //更改已经计算过的便于输出
        start->num = local;
        start = start->before;
    }
    //如果最终有进位则表示在最高位进位，增加节点
    if (carry != 0) {
        PtrToDigit carryNode = CreateDigitNode(carry);
        carryNode->next = numPtr;
        numPtr->before = carryNode;
        //移到头节点
        numPtr = numPtr->before;
    }
    return numPtr;
}

PtrToDigit Multi10(int count, PtrToDigit numPtr) {
    PtrToDigit zeroNode;
    PtrToDigit end;
    for (int i = 0; i < count; ++i) {
        zeroNode = CreateDigitNode(0);
        end = FindEnd(numPtr);
        end->next = zeroNode;
        zeroNode->before = end;
    }
    return numPtr;
}