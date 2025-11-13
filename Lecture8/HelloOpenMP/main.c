#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

// int main() {
// #pragma omp parallel
//     {
//         int id = omp_get_thread_num();
//         int n = omp_get_num_threads();
//         printf("Hello from thread %d of %d\n", id, n);
//     }
//     return 0;
// }

//----------------3.2-----------------
// int main() {
//     omp_set_num_threads(4);
//     int i;
// #pragma omp parallel for
//     for (int i = 0; i < 8; i++) {
//         int id = omp_get_thread_num();
//         // int id = i;
//         printf("i = %d be thread %d\n", i, id);
//     }
//     return 0;
// }

//----------------3.3-----------------
// int main() {
// #pragma omp parallel sections
//     {
// #pragma omp section
//         {
//             printf("Section 1: обчислення матриці\n");
//         }
//
// #pragma omp section
// {
//     printf("Section 2: читання файлу\n");
// }
//
// #pragma omp section
// {
//     printf("Section 3: запис результатів\n");
// }
//     }
//     return 0;
// }
//
//----------------4.3-----------------

// int main() {
//     const int N = 16;
//     double start, end;
//     omp_set_num_threads(4);
//
//     int owner[N];
//     start = omp_get_wtime();
//
// // #pragma omp parallel for schedule(static, 4)
// #pragma omp parallel for schedule(dynamic, 4)
// // #pragma omp parallel for schedule(guided, 4)
//     for (int i = 0; i < N; i++) {
//         int t = omp_get_thread_num();
//         // for (volatile long j = 0; j < 10000000; j++); // simulate workload
//         for (volatile long j = 0; j < (i + 1) * 500000000; j++);
//         printf("Iteration %2d job done by thread %d\n", i, t);
//         owner[i] = omp_get_thread_num();
//     }
//
//     end = omp_get_wtime();
//     printf("Execution time: %.3f sec\n", end - start);
//     // Print sequentially to show the mapping clearly
//     for (int i = 0; i < N; i++) {
//         printf("i=%2d handled by thread %d\n", i, owner[i]);
//     }
//     return 0;
// }
//----------------5.2-----------------

// int main() {
//     const int N = 80;
//     int array[N];
//     for (int i = 0; i < N; i++) array[i] = i + 1; // 1..8
//     // omp_set_num_threads(4);
//     int sum = 0;
// #pragma omp parallel for //reduction(+: sum)
//     for (int i = 0; i < N; i++) {
//         sum += array[i];
//     }
//
//     printf("Total sum = %d\n", sum);
//     return 0;
// }
//----------------6.4-----------------
// int main() {
//     putenv("OMP_CANCELLATION=true");
//     omp_set_num_threads(4);
// #pragma omp parallel for
//     for (int i = 0; i < 20; i++) {
//         printf("Thread %d processing i=%d\n", omp_get_thread_num(), i);
//         if (i == 1) {
//             printf("Thread %d: condition met, cancelling loop\n",
//                    omp_get_thread_num());
// #pragma omp cancel for
//         }
//         // Кожен потік перевіряє, чи не треба зупинитись
// #pragma omp cancellation point for
//         printf("Thread %d processing i=%d\n", omp_get_thread_num(), i);
//         for (volatile long j = 0; j < 100000000; j++);
//     }
//     return 0;
// }

//export OMP_NUM_THREADS=4; ./hello_omp

//----------------7.4-----------------
// #define N 100000000
// int main() {
//     double start, end;
//     double sum = 0.0;
//     double *arr = malloc(N * sizeof(double));
//     if (!arr) {
//         printf("Memory allocation failed!\n");
//         return 1;
//     }
//
//     for (int i = 0; i < N; i++) arr[i] = 1.0;
//
//     // Sequential version
//     start = omp_get_wtime();
//     for (int i = 0; i < N; i++)
//         sum += arr[i];
//     end = omp_get_wtime();
//     printf("Sequential sum = %.1f, time = %.3f sec\n", sum, end - start);
//
//     // Parallel version
//     sum = 0.0;
//     start = omp_get_wtime();
// #pragma omp parallel for reduction(+: sum)
//     for (int i = 0; i < N; i++)
//         sum += arr[i];
//     end = omp_get_wtime();
//     printf("Parallel sum = %.1f, time = %.3f sec\n", sum, end - start);
//
//     free(arr);
//
//     return 0;
// }
//----------------7.4-----------------
// int main() {
//     double *arr = malloc(N * sizeof(double));
//     if (!arr) {
//         printf("Memory allocation failed!\n");
//         return 1;
//     }
//
//     for (int i = 0; i < N; i++)
//         arr[i] = 1.0;
//
//     double sum = 0.0;
//     double start = omp_get_wtime();
//
// #pragma omp parallel for reduction(+: sum)
//     for (int i = 0; i < N; i++)
//         sum += arr[i];
//
//     double end = omp_get_wtime();
//
//     int threads = omp_get_max_threads();
//     printf("Threads used: %d\n", threads);
//     printf("Sum = %.1f\n", sum);
//     printf("Execution time: %.3f sec\n", end - start);
//
//     free(arr);
//     return 0;
// }
