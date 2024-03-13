#include <cstring>
#include "kernel.h"
#include "../../kernel/syscalls.h"
#include "../../dynamic_libs/os_functions.h"

static const int kernel_buffer_size = 256;
static char kernel_buffer[kernel_buffer_size];

void *kernel_memcpy(void *dst, void *src, size_t size) {
    int remain = size;
    char *dst_p = (char*)OSEffectiveToPhysical((void*)dst);
    char *src_p = (char*)src;

    while(remain > 0) {
        int copy_size = remain;
        if(copy_size > kernel_buffer_size) {
            copy_size = kernel_buffer_size;
        }

        memcpy(kernel_buffer, src_p, copy_size);
        SC0x25_KernelCopyData((unsigned int)dst_p, (unsigned int)kernel_buffer, copy_size);

        remain -= copy_size;
        dst_p += copy_size;
        src_p += copy_size;
    }

    return dst;
}

void *kernel_memcpy_flush(void *dst, void *src, size_t size) {
    void *ptr = kernel_memcpy(dst, src, size);

    DCFlushRange(dst, size);
    ICInvalidateRange(dst, size);

    return ptr;
}