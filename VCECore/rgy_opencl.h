﻿// -----------------------------------------------------------------------------------------
// NVEnc by rigaya
// -----------------------------------------------------------------------------------------
//
// The MIT License
//
// Copyright (c) 2014-2016 rigaya
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// ------------------------------------------------------------------------------------------

#ifndef __RGY_OPENCL_H__
#define __RGY_OPENCL_H__

#include "rgy_version.h"

#if ENABLE_OPENCL
#define CL_TARGET_OPENCL_VERSION 120
#include <CL/opencl.h>
#include <CL/cl_dx9_media_sharing.h>
#include <CL/cl_d3d11.h>
#include <vector>
#include <array>
#include <memory>
#include "rgy_osdep.h"
#include "rgy_log.h"

#ifndef CL_EXTERN
#define CL_EXTERN extern
#endif

CL_EXTERN void *(CL_API_CALL *f_clGetExtensionFunctionAddressForPlatform)(cl_platform_id  platform, const char *funcname);

CL_EXTERN cl_int (CL_API_CALL* f_clGetPlatformIDs)(cl_uint num_entries, cl_platform_id *platforms, cl_uint *num_platforms);
CL_EXTERN cl_int (CL_API_CALL* f_clGetPlatformInfo) (cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret);
CL_EXTERN cl_int (CL_API_CALL* f_clGetDeviceIDs) (cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id *devices, cl_uint *num_devices);
CL_EXTERN cl_int (CL_API_CALL* f_clGetDeviceInfo) (cl_device_id device, cl_device_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret);
CL_EXTERN cl_int (CL_API_CALL *f_clGetDeviceIDsFromDX9MediaAdapterKHR)(cl_platform_id platform, cl_uint num_media_adapters, cl_dx9_media_adapter_type_khr *media_adapter_type, void *media_adapters, cl_dx9_media_adapter_set_khr     media_adapter_set, cl_uint                          num_entries, cl_device_id *devices, cl_uint *num_devices);
CL_EXTERN cl_int (CL_API_CALL *f_clGetDeviceIDsFromD3D11KHR)(cl_platform_id platform, cl_d3d11_device_source_khr d3d_device_source, void *d3d_object, cl_d3d11_device_set_khr d3d_device_set, cl_uint num_entries, cl_device_id *devices, cl_uint *num_devices);

CL_EXTERN cl_context (CL_API_CALL* f_clCreateContext) (const cl_context_properties * properties, cl_uint num_devices, const cl_device_id * devices, void (CL_CALLBACK * pfn_notify)(const char *, const void *, size_t, void *), void * user_data, cl_int * errcode_ret);
CL_EXTERN cl_int (CL_API_CALL* f_clReleaseContext) (cl_context context);
CL_EXTERN cl_command_queue (CL_API_CALL* f_clCreateCommandQueue)(cl_context context, cl_device_id device, cl_command_queue_properties properties, cl_int * errcode_ret);
CL_EXTERN cl_int (CL_API_CALL* f_clReleaseCommandQueue) (cl_command_queue command_queue);

CL_EXTERN cl_program(CL_API_CALL* f_clCreateProgramWithSource) (cl_context context, cl_uint count, const char **strings, const size_t *lengths, cl_int *errcode_ret);
CL_EXTERN cl_int (CL_API_CALL* f_clBuildProgram) (cl_program program, cl_uint num_devices, const cl_device_id *device_list, const char *options, void (CL_CALLBACK *pfn_notify)(cl_program program, void *user_data), void* user_data);
CL_EXTERN cl_int (CL_API_CALL* f_clGetProgramBuildInfo) (cl_program program, cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret);
CL_EXTERN cl_int (CL_API_CALL* f_clGetProgramInfo)(cl_program program, cl_program_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret);
CL_EXTERN cl_int (CL_API_CALL* f_clReleaseProgram) (cl_program program);

CL_EXTERN cl_mem (CL_API_CALL* f_clCreateBuffer) (cl_context context, cl_mem_flags flags, size_t size, void *host_ptr, cl_int *errcode_ret);
CL_EXTERN cl_int (CL_API_CALL* f_clReleaseMemObject) (cl_mem memobj);
CL_EXTERN cl_kernel (CL_API_CALL* f_clCreateKernel) (cl_program program, const char *kernel_name, cl_int *errcode_ret);
CL_EXTERN cl_int (CL_API_CALL* f_clReleaseKernel) (cl_kernel kernel);
CL_EXTERN cl_int (CL_API_CALL* f_clSetKernelArg) (cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void *arg_value);
CL_EXTERN cl_int (CL_API_CALL* f_clEnqueueNDRangeKernel)(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t *global_work_offset, const size_t *global_work_size, const size_t *local_work_size, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event * event);
CL_EXTERN cl_int(CL_API_CALL* f_clEnqueueTask) (cl_command_queue command_queue, cl_kernel kernel, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);

CL_EXTERN cl_int(CL_API_CALL* f_clEnqueueReadBuffer) (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);
CL_EXTERN cl_int(CL_API_CALL* f_clEnqueueReadBufferRect)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t *buffer_offset, const size_t *host_offset, const size_t *region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);
CL_EXTERN cl_int(CL_API_CALL* f_clEnqueueWriteBuffer) (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);
CL_EXTERN cl_int(CL_API_CALL *f_clEnqueueWriteBufferRect)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t *buffer_offset, const size_t *host_offset, const size_t *region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);
CL_EXTERN cl_int(CL_API_CALL *f_clEnqueueCopyBuffer)(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);
CL_EXTERN cl_int(CL_API_CALL *f_clEnqueueCopyBufferRect)(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, const size_t *src_origin, const size_t *dst_origin, const size_t *region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);

CL_EXTERN cl_int(CL_API_CALL *f_clEnqueueCopyImage)(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const size_t src_origin[3], const size_t dst_origin[3], const size_t region[3], cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);
CL_EXTERN cl_int(CL_API_CALL *f_clEnqueueCopyImageToBuffer)(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_buffer, const size_t *src_origin[3], const size_t *region[3], size_t dst_offset, cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event *event);
CL_EXTERN cl_int(CL_API_CALL *f_clEnqueueCopyBufferToImage)(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_image, size_t src_offset, const size_t *dst_origin[3], const size_t *region[3], cl_uint num_events_in_wait_list, const cl_event * event_wait_list, cl_event *event);
CL_EXTERN void *(CL_API_CALL *f_clEnqueueMapBuffer)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event, cl_int *errcode_ret);
CL_EXTERN void *(CL_API_CALL *f_clEnqueueMapImage)(cl_command_queue  command_queue, cl_mem image, cl_bool blocking_map, cl_map_flags map_flags, const size_t *origin[3], const size_t *region[3], size_t *image_row_pitch, size_t *image_slice_pitch, cl_uint  num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event, cl_int *errcode_ret);
CL_EXTERN cl_int(CL_API_CALL *f_clEnqueueUnmapMemObject)(cl_command_queue command_queue, cl_mem memobj, void *mapped_ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);

CL_EXTERN cl_int(CL_API_CALL *f_clWaitForEvents)(cl_uint num_events, const cl_event *event_list);
CL_EXTERN cl_int(CL_API_CALL *f_clGetEventInfo)(cl_event event, cl_event_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret);
CL_EXTERN cl_event(CL_API_CALL *f_clCreateUserEvent)(cl_context context, cl_int *errcode_ret);
CL_EXTERN cl_int(CL_API_CALL *f_clRetainEvent)(cl_event event);
CL_EXTERN cl_int(CL_API_CALL *f_clReleaseEvent)(cl_event event);
CL_EXTERN cl_int(CL_API_CALL *f_clSetUserEventStatus)(cl_event event, cl_int execution_status);
CL_EXTERN cl_int(CL_API_CALL *f_clGetEventProfilingInfo)(cl_event event, cl_profiling_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret);

CL_EXTERN cl_int(CL_API_CALL *f_clFlush)(cl_command_queue command_queue);
CL_EXTERN cl_int(CL_API_CALL *f_clFinish)(cl_command_queue command_queue);

#define clGetExtensionFunctionAddressForPlatform f_clGetExtensionFunctionAddressForPlatform

#define clGetPlatformIDs f_clGetPlatformIDs
#define clGetPlatformInfo f_clGetPlatformInfo
#define clGetDeviceIDs f_clGetDeviceIDs
#define clGetDeviceInfo f_clGetDeviceInfo
#define clGetDeviceIDsFromDX9MediaAdapterKHR f_clGetDeviceIDsFromDX9MediaAdapterKHR
#define clGetDeviceIDsFromD3D11KHR f_clGetDeviceIDsFromD3D11KHR

#define clCreateContext f_clCreateContext
#define clReleaseContext f_clReleaseContext
#define clCreateCommandQueue f_clCreateCommandQueue
#define clReleaseCommandQueue f_clReleaseCommandQueue

#define clCreateProgramWithSource f_clCreateProgramWithSource
#define clBuildProgram f_clBuildProgram
#define clGetProgramBuildInfo f_clGetProgramBuildInfo
#define clGetProgramInfo f_clGetProgramInfo
#define clReleaseProgram f_clReleaseProgram

#define clCreateBuffer f_clCreateBuffer
#define clReleaseMemObject f_clReleaseMemObject
#define clCreateKernel f_clCreateKernel
#define clReleaseKernel f_clReleaseKernel
#define clSetKernelArg f_clSetKernelArg
#define clEnqueueNDRangeKernel f_clEnqueueNDRangeKernel
#define clEnqueueTask f_clEnqueueTask

#define clEnqueueReadBuffer f_clEnqueueReadBuffer
#define clEnqueueReadBufferRect f_clEnqueueReadBufferRect
#define clEnqueueWriteBuffer f_clEnqueueWriteBuffer
#define clEnqueueWriteBufferRect f_clEnqueueWriteBufferRect
#define clEnqueueCopyBuffer f_clEnqueueCopyBuffer
#define clEnqueueCopyBufferRect f_clEnqueueCopyBufferRect

#define clEnqueueCopyImage f_clEnqueueCopyImage
#define clEnqueueCopyImageToBuffer f_clEnqueueCopyImageToBuffer
#define clEnqueueCopyBufferToImage f_clEnqueueCopyBufferToImage
#define clEnqueueMapBuffer f_clEnqueueMapBuffer
#define clEnqueueMapImage f_clEnqueueMapImage
#define clEnqueueUnmapMemObject f_clEnqueueUnmapMemObject

#define clWaitForEvents f_clWaitForEvents
#define clGetEventInfo f_clGetEventInfo
#define clCreateUserEvent f_clCreateUserEvent
#define clRetainEvent f_clRetainEvent
#define clReleaseEvent f_clReleaseEvent
#define clSetUserEventStatus f_clSetUserEventStatus
#define clGetEventProfilingInfo f_clGetEventProfilingInfo

#define clFlush f_clFlush
#define clFinish f_clFinish

MAP_PAIR_0_1_PROTO(err, rgy, RGY_ERR, cl, cl_int);

static const TCHAR *cl_errmes(cl_int err) {
    return get_err_mes(err_cl_to_rgy(err));
}

enum RGYCLMemcpyKind {
    RGYCLMemcpyD2D,
    RGYCLMemcpyD2H,
    RGYCLMemcpyH2D,
    RGYCLMemcpyH2H,
};

static inline RGYCLMemcpyKind getMemcpyKind(bool inputDevice, bool outputDevice) {
    if (inputDevice) {
        return (outputDevice) ? RGYCLMemcpyD2D : RGYCLMemcpyD2H;
    } else {
        return (outputDevice) ? RGYCLMemcpyH2D : RGYCLMemcpyH2H;
    }
}

static const TCHAR *getMemcpyKindStr(RGYCLMemcpyKind kind) {
    switch (kind) {
    case RGYCLMemcpyD2D:
        return _T("copyDtoD");
    case RGYCLMemcpyD2H:
        return _T("copyDtoH");
    case RGYCLMemcpyH2D:
        return _T("copyHtoD");
    case RGYCLMemcpyH2H:
        return _T("copyHtoH");
    default:
        return _T("copyUnknown");
    }
}

static const TCHAR *getMemcpyKindStr(bool inputDevice, bool outputDevice) {
    return getMemcpyKindStr(getMemcpyKind(inputDevice, outputDevice));
}

struct RGYCLBuf {
    cl_mem mem;
    cl_mem_flags flags;
    size_t size;

    RGYCLBuf(cl_mem mem_, cl_mem_flags flags_, size_t size_) : mem(mem_), flags(flags_), size(size_) {
    };
    ~RGYCLBuf() {
        if (mem) {
            clReleaseMemObject(mem);
        }
    }
protected:
    RGYCLBuf(const RGYCLBuf &) = delete;
    void operator =(const RGYCLBuf &) = delete;
};

struct RGYCLBufFrame {
public:
    FrameInfo frame;
    cl_mem_flags flags;
    RGYCLBufFrame()
        : frame({ 0 }), flags(0) {
    };
    RGYCLBufFrame(const FrameInfo &info_, cl_mem_flags flags_ = CL_MEM_READ_WRITE)
        : frame(info_), flags(flags_) {
    };
    RGY_ERR alloc() {

    }
protected:
    RGYCLBufFrame(const RGYCLBufFrame &) = delete;
    void operator =(const RGYCLBufFrame &) = delete;
public:
    cl_mem& mem(int i) {
        return (cl_mem&)frame.ptr[i];
    }
    void clear() {
        for (int i = 0; i < _countof(frame.ptr); i++) {
            if (mem(i)) {
                clReleaseMemObject(mem(i));
                mem(i) = nullptr;
            }
            frame.pitch[i] = 0;
        }
    }
    ~RGYCLBufFrame() {
        clear();
    }
};

struct RGYOpenCLDeviceInfo {
    cl_device_type type;
    int vendor_id;
    int max_compute_units;
    int max_clock_frequency;
    int max_samplers;
    uint64_t global_mem_size;
    size_t profiling_timer_resolution;
    std::string name;
    std::string vendor;
    std::string driver_version;
    std::string profile;
    std::string version;
    std::string extensions;
};

class RGYOpenCLDevice {
public:
    RGYOpenCLDevice(cl_device_id device);
    virtual ~RGYOpenCLDevice() {};
    RGYOpenCLDeviceInfo info();
    tstring infostr();
protected:
    cl_device_id m_device;
};

struct RGYOpenCLPlatformInfo {
    std::string profile;
    std::string version;
    std::string name;
    std::string vendor;
    std::string extension;
};

class RGYOpenCLPlatform {
public:
    RGYOpenCLPlatform(cl_platform_id platform, shared_ptr<RGYLog> pLog);
    virtual ~RGYOpenCLPlatform() {};
    RGY_ERR createDeviceList(cl_device_type device_type);
    RGY_ERR createDeviceListD3D9(cl_device_type device_type, void *d3d9dev);
    RGY_ERR createDeviceListD3D11(cl_device_type device_type, void *d3d11dev);
    cl_platform_id get() const { return m_platform; };
    const void *d3d9dev() const { return m_d3d9dev; };
    const void *d3d11dev() const { return m_d3d11dev; };
    std::vector<cl_device_id>& devs() { return m_devices; };
    cl_device_id dev(int idx) { return m_devices[idx]; };
    const std::vector<cl_device_id>& devs() const { return m_devices; };
    void setDev(cl_device_id dev) { m_devices.clear(); m_devices.push_back(dev); };
    void setDev(cl_device_id dev, void *d3d9dev, void *d3d11dev) {
        m_devices.clear(); m_devices.push_back(dev);
        if (d3d9dev) m_d3d9dev = d3d9dev;
        if (d3d11dev) m_d3d11dev = d3d11dev;
    };
    void setDevs(std::vector<cl_device_id> &devs) { m_devices = devs; };
    bool isVendor(const char *vendor);
protected:
    RGYOpenCLPlatformInfo info();

    cl_platform_id m_platform;
    void *m_d3d9dev;
    void *m_d3d11dev;
    std::vector<cl_device_id> m_devices;
    shared_ptr<RGYLog> m_pLog;
};

struct RGYWorkSize {
    size_t w[3];
    RGYWorkSize() {
        w[0] = w[1] = w[2] = 1;
    }
    RGYWorkSize(size_t x) {
        w[0] = x;
        w[1] = w[2] = 1;
    };
    RGYWorkSize(size_t x, size_t y) {
        w[0] = x;
        w[1] = y;
        w[2] = 1;
    }
    RGYWorkSize(size_t x, size_t y, size_t z) {
        w[0] = x;
        w[1] = y;
        w[2] = z;
    }
    const size_t *operator()() const {
        return &w[0];
    }
};

class RGYOpenCLKernelLauncher {
public:
    RGYOpenCLKernelLauncher(cl_kernel kernel, std::string kernelName, cl_command_queue queue, const RGYWorkSize &local, const RGYWorkSize &global, shared_ptr<RGYLog> pLog);
    virtual ~RGYOpenCLKernelLauncher() {};

    RGY_ERR launch(std::vector<void *> arg_ptrs = std::vector<void *>(), std::vector<size_t> arg_size = std::vector<size_t>()) const;

    template <typename... ArgTypes>
    RGY_ERR operator()(ArgTypes... args) const {
        return launch(args...);
    }
    template <typename... ArgTypes>
    RGY_ERR launch(ArgTypes... args) const {
        return this->launch(
            std::vector<void *>({ (void *)&args... }),
            std::vector<size_t>({ sizeof(args)... })
        );
    }
protected:
    cl_kernel m_kernel;
    std::string m_kernelName;
    cl_command_queue m_queue;
    RGYWorkSize m_local;
    RGYWorkSize m_global;
    shared_ptr<RGYLog> m_pLog;
};

class RGYOpenCLKernel {
public:
    RGYOpenCLKernel() : m_kernel(), m_kernelName(), m_pLog() {};
    RGYOpenCLKernel(cl_kernel kernel, std::string kernelName, shared_ptr<RGYLog> pLog);
    virtual ~RGYOpenCLKernel() {};
    RGYOpenCLKernelLauncher config(cl_command_queue queue, const RGYWorkSize& local, const RGYWorkSize& global);
protected:
    cl_kernel m_kernel;
    std::string m_kernelName;
    shared_ptr<RGYLog> m_pLog;
};

class RGYOpenCLProgram {
public:
    RGYOpenCLProgram(cl_program program, shared_ptr<RGYLog> pLog);
    virtual ~RGYOpenCLProgram() {};

    RGYOpenCLKernel kernel(const char *kernelName);
protected:
    cl_program m_program;
    shared_ptr<RGYLog> m_pLog;
};

typedef std::unique_ptr<std::remove_pointer<cl_context>::type, decltype(clReleaseContext)> unique_context;
typedef std::unique_ptr<std::remove_pointer<cl_command_queue>::type, decltype(clReleaseCommandQueue)> unique_queue;

class RGYOpenCLContext {
public:
    RGYOpenCLContext(shared_ptr<RGYOpenCLPlatform> platform, shared_ptr<RGYLog> pLog);
    virtual ~RGYOpenCLContext();

    RGY_ERR createContext();
    cl_context context() const { return m_context.get(); };
    cl_command_queue queue(int idx=0) const { return m_queue[idx].get(); };
    RGYOpenCLPlatform *platform() const { return m_platform.get(); };

    unique_ptr<RGYOpenCLProgram> build(const std::string& source);
    unique_ptr<RGYOpenCLProgram> buildFile(const tstring &filename);
    unique_ptr<RGYOpenCLProgram> buildResource(const TCHAR *name, const TCHAR *type);

    unique_ptr<RGYCLBuf> createBuffer(size_t size, cl_mem_flags flags = CL_MEM_READ_WRITE, void *host_ptr = nullptr);
    unique_ptr<RGYCLBufFrame> createFrameBuffer(const FrameInfo &frame, cl_mem_flags flags = CL_MEM_READ_WRITE);
    RGY_ERR copyFrame(FrameInfo *dst, const FrameInfo *src, const sInputCrop *srcCrop = nullptr, int queue_id = 0);
protected:
    unique_ptr<RGYOpenCLProgram> build(const char *data, const size_t size);

    shared_ptr<RGYOpenCLPlatform> m_platform;
    unique_context m_context;
    std::vector<unique_queue> m_queue;
    shared_ptr<RGYLog> m_pLog;
};

class RGYOpenCL {
public:
    static HMODULE openCLHandle;
    static bool openCLCrush;

    RGYOpenCL();
    RGYOpenCL(shared_ptr<RGYLog> pLog);
    virtual ~RGYOpenCL();

    std::vector<shared_ptr<RGYOpenCLPlatform>> getPlatforms(const char *vendor = nullptr);
protected:
    shared_ptr<RGYLog> m_pLog;
};

int initOpenCLGlobal();

#endif //ENABLE_OPENCL

#endif //__RGY_OPENCL_H__