/* search_math.c — Difficolta: MEDIA
 * Ricerca binaria + funzioni matematiche (usa libm). Mix di control flow
 * e chiamate a funzioni esterne (sqrt, pow) che il decompilatore deve riconoscere. */
#include <stdio.h>
#include <math.h>

int binary_search(int *arr, int n, int target) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

double vector_magnitude(double *v, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += pow(v[i], 2);
    return sqrt(sum);
}

int is_prime(int x) {
    if (x < 2) return 0;
    for (int i = 2; (long)i * i <= x; i++)
        if (x % i == 0) return 0;
    return 1;
}

int main(void) {
    int sorted[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int n = sizeof(sorted) / sizeof(sorted[0]);
    printf("Indice di 7: %d\n", binary_search(sorted, n, 7));
    printf("Indice di 8: %d\n", binary_search(sorted, n, 8));

    double v[] = {3.0, 4.0};
    printf("Magnitudine: %.2f\n", vector_magnitude(v, 2));

    printf("Primi fino a 20: ");
    for (int i = 0; i <= 20; i++)
        if (is_prime(i)) printf("%d ", i);
    printf("\n");
    return 0;
}
