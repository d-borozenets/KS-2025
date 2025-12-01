#ifndef __OPENCL_MINIMAL_H__
#define __OPENCL_MINIMAL_H__

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================*/
/*                      BASIC TYPES                          */
/*===========================================================*/

typedef int               cl_int;
typedef unsigned int      cl_uint;
typedef unsigned long     cl_ulong;
typedef unsigned short    cl_ushort;
typedef unsigned char     cl_uchar;
typedef size_t            cl_bool;
typedef size_t            cl_bitfield;

typedef struct _cl_platform_id  * cl_platform_id;
typedef struct _cl_device_id    * cl_device_id;
typedef struct _cl_context      * cl_context;
typedef struct _cl_command_queue * cl_command_queue;
typedef struct _cl_mem          * cl_mem;
typedef struct _cl_program      * cl_program;
typedef struct _cl_kernel       * cl_kernel;
typedef struct _cl_event        * cl_event;
typedef struct _cl_sampler      * cl_sampler;

/*===========================================================*/
/*                         CONSTANTS                         */
/*===========================================================*/

#define CL_SUCCESS                                  0
#define CL_DEVICE_TYPE_DEFAULT                      (1 << 0)
#define CL_DEVICE_TYPE_CPU                          (1 << 1)
#define CL_DEVICE_TYPE_GPU                          (1 << 2)
#define CL_DEVICE_TYPE_ALL                          0xFFFFFFFF

#define CL_MEM_READ_WRITE                           (1 << 0)
#define CL_MEM_WRITE_ONLY                           (1 << 1)
#define CL_MEM_READ_ONLY                            (1 << 2)
#define CL_MEM_USE_HOST_PTR                         (1 << 3)
#define CL_MEM_ALLOC_HOST_PTR                       (1 << 4)
#define CL_MEM_COPY_HOST_PTR                        (1 << 5)

#define CL_PROGRAM_BUILD_LOG                        0x1183

/*===========================================================*/
/*                 PLATFORM API FUNCTIONS                    */
/*===========================================================*/

cl_int clGetPlatformIDs(
    cl_uint num_entries,
    cl_platform_id *platforms,
    cl_uint *num_platforms);

cl_int clGetPlatformInfo(
    cl_platform_id platform,
    cl_uint param_name,
    size_t param_value_size,
    void *param_value,
    size_t *param_value_size_ret);

/*===========================================================*/
/*                  DEVICE API FUNCTIONS                     */
/*===========================================================*/

cl_int clGetDeviceIDs(
    cl_platform_id platform,
    cl_bitfield device_type,
    cl_uint num_entries,
    cl_device_id *devices,
    cl_uint *num_devices);

/*===========================================================*/
/*                 CONTEXT / QUEUE API                       */
/*===========================================================*/

typedef void (*_cl_notify)(const char *, const void *, size_t, void *);

cl_context clCreateContext(
    const void *properties,
    cl_uint num_devices,
    const cl_device_id *devices,
    _cl_notify pfn_notify,
    void *user_data,
    cl_int *errcode_ret);


cl_command_queue clCreateCommandQueue(
    cl_context context,
    cl_device_id device,
    cl_bitfield properties,
    cl_int *errcode_ret);

/*===========================================================*/
/*                     MEMORY FUNCTIONS                      */
/*===========================================================*/

cl_mem clCreateBuffer(
    cl_context context,
    cl_bitfield flags,
    size_t size,
    void *host_ptr,
    cl_int *errcode_ret);

/*===========================================================*/
/*                  PROGRAM / KERNEL API                     */
/*===========================================================*/

cl_program clCreateProgramWithSource(
    cl_context context,
    cl_uint count,
    const char **strings,
    const size_t *lengths,
    cl_int *errcode_ret);

cl_int clBuildProgram(
    cl_program program,
    cl_uint num_devices,
    const cl_device_id *device_list,
    const char *options,
    void (*pfn_notify)(cl_program program, void *user_data),
    void *user_data);

cl_int clGetProgramBuildInfo(
    cl_program program,
    cl_device_id device,
    cl_uint param_name,
    size_t param_value_size,
    void *param_value,
    size_t *param_value_size_ret);

cl_kernel clCreateKernel(
    cl_program program,
    const char *kernel_name,
    cl_int *errcode_ret);

cl_int clSetKernelArg(
    cl_kernel kernel,
    cl_uint arg_index,
    size_t arg_size,
    const void *arg_value);

/*===========================================================*/
/*                      EXECUTION API                        */
/*===========================================================*/

cl_int clEnqueueNDRangeKernel(
    cl_command_queue command_queue,
    cl_kernel kernel,
    cl_uint work_dim,
    const size_t *global_work_offset,
    const size_t *global_work_size,
    const size_t *local_work_size,
    cl_uint num_events_in_wait_list,
    const cl_event *event_wait_list,
    cl_event *event);

cl_int clFinish(
    cl_command_queue command_queue);

/*===========================================================*/
/*                      READ / WRITE API                     */
/*===========================================================*/

cl_int clEnqueueReadBuffer(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_read,
    size_t offset,
    size_t cb,
    void *ptr,
    cl_uint num_events_in_wait_list,
    const cl_event *event_wait_list,
    cl_event *event);

/*===========================================================*/

#ifdef __cplusplus
}
#endif

#endif
