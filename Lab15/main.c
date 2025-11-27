#include <math.h>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 10000000
#define M 10000

double heavy(int i) {
    double x = 0;
    int loops = (i % 1000) * 100; // нерівномірність
    for (int k = 0; k < loops; k++) {
        x += sin(k) * tan(k % 7);
    }
    return x;
}

void hello_from_threads() {
    printf("Hello from threads\n");
}

void sequential_fill() {
    printf("sequential fill\n");
    double *arr = malloc(N * sizeof(double));


    free(arr);
}

void parallel_fill() {
    printf("parallel fill\n");
}

void schedule_test() {
    printf("schedule test \n");
    double start = 0;
    double end = 0;
    double *arr = malloc(N * sizeof(double));




    free(arr);
}


void pi_monte_carlo(int num_threads) {
    printf("pi_monte_carlo\n");
    long long total = 50000000;
    long long inside = 0;

    double pi = 4.0 * (double) inside / total;
    // printf("num_threads:%d pi: %.4f, time:%.4f\n",num_threads, pi, end - start);
}

int main(void) {

    // hello_from_threads();
    // sequential_fill();
    // parallel_fill();
    // schedule_test();
    // pi_monte_carlo(1);
    // pi_monte_carlo(4);
    // pi_monte_carlo(8);
    return 0;
}
