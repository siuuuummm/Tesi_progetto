/* bubble_sort.c — Difficolta: FACILE
 * Loop annidati semplici, swap. Buon baseline per la profondita AST. */
#include <stdio.h>

void bubble_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int main(void) {
    int data[] = {5, 2, 9, 1, 7, 3, 8, 4, 6, 0};
    int n = sizeof(data) / sizeof(data[0]);
    bubble_sort(data, n);
    for (int i = 0; i < n; i++)
        printf("%d ", data[i]);
    printf("\n");
    return 0;
}
