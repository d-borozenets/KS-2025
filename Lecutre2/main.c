#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef __aarch64__
#else
#include <xmmintrin.h>   // SSE
#include <immintrin.h>   // AVX (на майбутнє)
#endif


#define N 4
#define REPEAT 2000000000  // кількість повторів

// Функція для вимірювання часу
double get_time_in_seconds() {
    return (double) clock() / CLOCKS_PER_SEC;
}

// ==========================================
// Варіант 1 — Звичайне послідовне додавання
// ==========================================
void add_scalar(float *a, float *b, float *c) {
    double start = get_time_in_seconds();

    for (int n = 0; n < REPEAT; n++) {
        for (int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }
    }

    double end = get_time_in_seconds();
    printf("[Scalar] Time: %.6f s\n", end - start);
}


#ifdef __aarch64__
void add_asm_neon(float *a, float *b, float *c) {
    double start = get_time_in_seconds();
    for (int n = 0; n < REPEAT; n++) {
        __asm__ volatile(
            "ld1 {v0.4s}, [%0]     \n\t" // v0 = a[0..3]
            "ld1 {v1.4s}, [%1]     \n\t" // v1 = b[0..3]
            "fadd v0.4s, v0.4s, v1.4s \n\t" // v0 = v0 + v1
            "st1 {v0.4s}, [%2]     \n\t" // c = v0
            :
            : "r"(a), "r"(b), "r"(c)
            : "v0", "v1"
        );
    }

    double end = get_time_in_seconds();
    printf("[ASM Neon] Time: %.6f s\n", end - start);
}
#else

void add_sse(float *a, float *b, float *c) {
    double start = get_time_in_seconds();

    __m128 va, vb, vc;
    for (int n = 0; n < REPEAT; n++) {
        va = _mm_loadu_ps(a);
        vb = _mm_loadu_ps(b);
        vc = _mm_add_ps(va, vb);
        _mm_storeu_ps(c, vc);
    }

    double end = get_time_in_seconds();
    printf("[SSE] Time: %.6f s\n", end - start);
}


void add_asm(float *a, float *b, float *c) {
    double start = get_time_in_seconds();

    for (int n = 0; n < REPEAT; n++) {
        __asm__ volatile (
            "movups (%0), %%xmm0\n\t"
            "movups (%1), %%xmm1\n\t"
            "addps %%xmm1, %%xmm0\n\t"
            "movups %%xmm0, (%2)\n\t"
            :
            : "r"(a), "r"(b), "r"(c)
            : "%xmm0", "%xmm1"
        );
    }

    double end = get_time_in_seconds();
    printf("[ASM] Time: %.6f s\n", end - start);
}
#endif


// ==========================================
// MAIN
// ==========================================
int main() {
    float a[N] = {1.0f, 2.0f, 3.0f, 4.0f};
    float b[N] = {5.0f, 6.0f, 7.0f, 8.0f};
    float c[N] = {0.0f, 0.0f, 0.0f, 0.0f};

    printf("Vector addition demo (N=%d, repeats=%d)\n\n", N, REPEAT);

    add_scalar(a, b, c);

#ifdef __aarch64__
    add_asm_neon(a, b, c);
#else
    add_sse(a, b, c);
    add_asm(a, b, c);
#endif

    printf("\nFinal result: ");
    for (int i = 0; i < N; i++)
        printf("%.1f ", c[i]);
    printf("\n");

    return 0;
}
