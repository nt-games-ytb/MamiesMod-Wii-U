#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "types.hpp"
#include "cache.h"
#include "syscall.h"

inline void kernel_write_value(uint32_t address, uint32_t value) {
    int32_t *kernelBuffer = (int32_t*)(0x1000000 - 0x100);
    kernelBuffer[0] = value;
    WiiU::Syscall::SC0x25_KernelCopyData(WiiU::Syscall::SC0x2_EffectiveToPhysical(address), (uint32_t)kernelBuffer, sizeof(int32_t));
    WiiU::DCFlushRange(address, sizeof(int32_t));
    WiiU::ICInvalidateRange(address, sizeof(int32_t));
}

#endif