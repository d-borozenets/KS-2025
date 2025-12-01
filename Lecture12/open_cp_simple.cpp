#include <CL/cl.h>
#include <iostream>
using namespace std;

// ------------------------------------------------------
// 1. Найпростіший можливий OpenCL kernel
// ------------------------------------------------------
const char* kernelSource = R"CLC(
__kernel void vector_add(__global float* a,
                         __global float* b,
                         __global float* c)
{
    int i = get_global_id(0); // індекс потоку
    c[i] = a[i] + b[i];       // робимо додавання
}
)CLC";

int main() {
    const int N = 5;
    float a[N] = {1,2,3,4,5};
    float b[N] = {10,20,30,40,50};
    float c[N];

    // ------------------------------------------------------
    // 2. Платформа + пристрій (беремо “перший-ліпший”)
    // ------------------------------------------------------
    cl_platform_id  platform;
    cl_device_id    device;
    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_DEFAULT, 1, &device, NULL);

    // ------------------------------------------------------
    // 3. Контекст + черга команд
    // ------------------------------------------------------
    cl_context context = clCreateContext(0, 1, &device, 0, 0, 0);
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, 0);

    // ------------------------------------------------------
    // 4. Створюємо буфери на GPU
    // ------------------------------------------------------
    cl_mem d_a = clCreateBuffer(context, CL_MEM_READ_ONLY  | CL_MEM_COPY_HOST_PTR, N*sizeof(float), a, 0);
    cl_mem d_b = clCreateBuffer(context, CL_MEM_READ_ONLY  | CL_MEM_COPY_HOST_PTR, N*sizeof(float), b, 0);
    cl_mem d_c = clCreateBuffer(context, CL_MEM_WRITE_ONLY,                      N*sizeof(float),    0, 0);

    // ------------------------------------------------------
    // 5. Компіяціюємо kernel
    // ------------------------------------------------------
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSource, 0, 0);
    clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    cl_kernel kernel = clCreateKernel(program, "vector_add", 0);

    // Аргументи
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_b);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_c);

    // ------------------------------------------------------
    // 6. Запуск кернела: запускаємо N потоків
    // ------------------------------------------------------
    size_t globalSize = N;
    clEnqueueNDRangeKernel(queue, kernel, 1, 0, &globalSize, 0, 0, NULL, NULL);

    // Чекаємо результатів
    clFinish(queue);

    // ------------------------------------------------------
    // 7. Зчитуємо результат назад
    // ------------------------------------------------------
    clEnqueueReadBuffer(queue, d_c, CL_TRUE, 0, N*sizeof(float), c, 0, 0, 0);

    // ------------------------------------------------------
    // 8. Виводимо результат
    // ------------------------------------------------------
    for (int i=0; i<N; i++)
        cout << c[i] << " ";
    cout << endl;

    return 0;
}
