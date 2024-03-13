#pragma once

#include "types.hpp"

namespace WiiU {

class Syscall {
public:

	static inline uint32_t SC0x2_EffectiveToPhysical(uint32_t effect) {
		volatile uint32_t ret = 0;
		asm volatile("mr 3, %[effect] \n"
            "li 0, 0x200 \n"
            "sc \n"
			"mr %[ret], 3 \n"
            : [ret] "+r" (ret)
            : [effect] "r" (effect)
            : "lr", "ctr", "r0", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12");
		return ret;
	}
	
    static inline void SC0x25_KernelCopyData(uint32_t phys_dst, const uint32_t phys_src, uint32_t length) {
        asm volatile("mr 3, %[dst] \n"
            "mr 4, %[src] \n"
            "mr 5, %[len] \n"
            "li 0, 0x2500 \n"
            "sc \n"
            :
            : [dst] "r" (phys_dst), [src] "r" (phys_src), [len] "r" (length)
            : "lr", "ctr", "r0", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12");
    }
};

}