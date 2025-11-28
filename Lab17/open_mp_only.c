#include <math.h>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>


int main(void) {
    printf("open mp only \n");
    double start = 0;
    double end = 0;

    long long count = 500000000;
    double *a = malloc(count * sizeof(double));
    if (!a) {
        printf("Memory allocation error!\n");
        return 1;
    }
    // TODO: ініціалізувати масив
    // TODO: паралельний цикл з reduction
    // TODO: час і вивід

    // printf("sum: %.4f, time: %.4f\n", sum, end - start);

    free(a);
    return 0;
}
