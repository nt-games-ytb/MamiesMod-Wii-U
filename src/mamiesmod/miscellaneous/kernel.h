#ifndef MML_KERNEL_H_
#define MML_KERNEL_H_

#include <stddef.h>

void *kernel_memcpy(void *dst, void *src, size_t size);
void *kernel_memcpy_flush(void *dst, void *src, size_t size);

template<typename T>
void kernel_write_value(void *dst, T value) {
    kernel_memcpy_flush(dst, &value, sizeof(T));
}

template<typename T>
T kernel_read_value(void *src) {
    T buf;
    kernel_memcpy_flush(&buf, src, sizeof(T));
    return buf;
}

#endif