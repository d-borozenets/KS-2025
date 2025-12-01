#include <stdio.h>
#include "CL/opencl.h"

const char* kernelSrc =
"__kernel void add(__global float* A, __global float* B, __global float* C) {"
"   int id = get_global_id(0);"
"   C[id] = A[id] + B[id];"
"}";

int run_gpu() {
    cl_int err;

    // --- 1. Отримуємо платформу ---
    cl_platform_id platform;
    err = clGetPlatformIDs(1, &platform, NULL);
    if (err != CL_SUCCESS) {
        printf("clGetPlatformIDs error: %d\n", err);
        return 1;
    }

    // --- 2. Отримуємо пристрій ---
    cl_device_id device;
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_DEFAULT, 1, &device, NULL);
    if (err != CL_SUCCESS) {
        printf("clGetDeviceIDs error: %d\n", err);
        return 1;
    }

    // --- 3. Контекст + черга ---
    cl_context ctx = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    if (!ctx) { printf("Context error\n"); return 1; }

    cl_command_queue queue = clCreateCommandQueue(ctx, device, 0, &err);
    if (!queue) { printf("Queue error\n"); return 1; }

    // --- 4. Дані ---
    const int N = 16;
    float A[N], B[N], C[N];
    for (int i = 0; i < N; i++) {
        A[i] = i;
        B[i] = 100 + i;
    }

    cl_mem bufA = clCreateBuffer(ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                 sizeof(float)*N, A, &err);
    cl_mem bufB = clCreateBuffer(ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                 sizeof(float)*N, B, &err);
    cl_mem bufC = clCreateBuffer(ctx, CL_MEM_WRITE_ONLY,
                                 sizeof(float)*N, NULL, &err);

    // --- 5. Програма + ядро ---
    cl_program program = clCreateProgramWithSource(ctx, 1, &kernelSrc, NULL, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);

    if (err != CL_SUCCESS) {
        printf("Build error: %d\n", err);
        return 1;
    }

    cl_kernel kernel = clCreateKernel(program, "add", &err);

    clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufA);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufB);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufC);

    // --- 6. Запуск ---
    size_t global = N;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global, NULL, 0, NULL, NULL);
    clFinish(queue);

    // --- 7. Читаємо дані ---
    clEnqueueReadBuffer(queue, bufC, 1, 0, sizeof(float)*N, C, 0, NULL, NULL);

    // --- 8. Вивід ---
    for (int i = 0; i < N; i++)
        printf("%d: %.1f + %.1f = %.1f\n", i, A[i], B[i], C[i]);
    return 0;
}

int main() {
    run_gpu();
    return 0;
}
