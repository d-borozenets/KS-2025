#include <CL/cl.h>
#include <iostream>
#include <vector>
using namespace std;

// ===============================
// OpenCL kernel code
// ===============================
const char* kernelSource = R"CLC(
__kernel void vector_add(__global const float* a,
                         __global const float* b,
                         __global float* c,
                         int n)
{
    int idx = get_global_id(0);
    if (idx < n)
        c[idx] = a[idx] + b[idx];
}
)CLC";

int main() {
    const int N = 10;
    size_t bytes = N * sizeof(float);

    // ===============================
    // 1. Підготовка даних на CPU
    // ===============================
    vector<float> h_a(N), h_b(N), h_c(N);

    for (int i = 0; i < N; i++) {
        h_a[i] = i;
        h_b[i] = 100 + i;
    }

    // ===============================
    // 2. Знаходимо OpenCL платформу і пристрій
    // ===============================
    cl_platform_id platform;
    cl_device_id device;

    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_DEFAULT, 1, &device, NULL);

    // ===============================
    // 3. Створюємо контекст і чергу команд
    // ===============================
    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);

    // Command Queue — черга завдань для GPU/CPU
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, NULL);

    // ===============================
    // 4. Створюємо буфери на пристрої
    // ===============================
    cl_mem d_a = clCreateBuffer(context, CL_MEM_READ_ONLY  | CL_MEM_COPY_HOST_PTR, bytes, h_a.data(), NULL);
    cl_mem d_b = clCreateBuffer(context, CL_MEM_READ_ONLY  | CL_MEM_COPY_HOST_PTR, bytes, h_b.data(), NULL);
    cl_mem d_c = clCreateBuffer(context, CL_MEM_WRITE_ONLY, bytes, NULL, NULL);

    // ===============================
    // 5. Створюємо і компілюємо програму
    // ===============================
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSource, NULL, NULL);
    clBuildProgram(program, 1, &device, NULL, NULL, NULL);

    // ===============================
    // 6. Створюємо kernel
    // ===============================
    cl_kernel kernel = clCreateKernel(program, "vector_add", NULL);

    // Встановлюємо аргументи кернела
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_b);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_c);
    clSetKernelArg(kernel, 3, sizeof(int),    &N);

    // ===============================
    // 7. Запускаємо kernel
    // ===============================
    size_t globalSize = N;     // стільки потоків хочемо
    size_t localSize  = 1;     // можна дати 1, GPU сам оптимізує

    clEnqueueNDRangeKernel(queue, kernel, 1, NULL,
                           &globalSize, &localSize,
                           0, NULL, NULL);

    // Чекаємо завершення
    clFinish(queue);

    // ===============================
    // 8. Читаємо результат назад
    // ===============================
    clEnqueueReadBuffer(queue, d_c, CL_TRUE, 0, bytes, h_c.data(), 0, NULL, NULL);

    // ===============================
    // 9. Виводимо результат
    // ===============================
    cout << "Result: ";
    for (int i = 0; i < N; i++)
        cout << h_c[i] << " ";
    cout << endl;

    // ===============================
    // 10. Прибираємо ресурси
    // ===============================
    clReleaseMemObject(d_a);
    clReleaseMemObject(d_b);
    clReleaseMemObject(d_c);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    return 0;
}
