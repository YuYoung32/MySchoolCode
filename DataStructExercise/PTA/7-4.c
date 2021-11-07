#include <stdio.h>
#include <stdlib.h>

int main() {
    int k;
    int *num = (int *) malloc(1000000 * sizeof(int));
    int i = -1;
    scanf("%d", &k);
    do {
        i++;
        scanf("%d", &num[i]);
    } while (num[i] >= 0);
    //错误位置
    if (k > i) {
        printf("NULL\n");
        return 0;
    }
    printf("%d\n", num[i - k]);
    free(num);
    return 0;
}