#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int num[n];
    for (int j = 0; j < n; ++j) {
        scanf("%d", &num[j]);
    }
    int start = 0, end = 0;
    int saveStart, saveEnd;
    saveStart = start;
    saveEnd = end;
    for (int j = 0; j < n; ++j) {
        if (j && num[j] > num[j - 1]) {
            end = j;
        } else {
            start = j;
        }
        if (end - start > saveEnd - saveStart) {
            saveStart = start;
            saveEnd = end;
        }
    }
    int cnt = 0;
    for (int j = saveStart; j <= saveEnd; ++j) {
        if (cnt++) {
            printf(" ");
        }
        printf("%d", num[j]);
    }
    return 0;
}