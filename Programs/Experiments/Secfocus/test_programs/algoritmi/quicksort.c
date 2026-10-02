/* quicksort.c — Difficolta: MEDIA
 * Ricorsione + partizione. La ricorsione spesso confonde i decompilatori
 * a livelli O2/O3 per via dell'inlining e tail-call optimization. */
#include <stdio.h>

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    int tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;
    return i + 1;
}

void quicksort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int main(void) {
    int data[] = {10, 7, 8, 9, 1, 5, 3, 6, 2, 4};
    int n = sizeof(data) / sizeof(data[0]);
    quicksort(data, 0, n - 1);
    for (int i = 0; i < n; i++)
        printf("%d ", data[i]);
    printf("\n");
    return 0;
}
