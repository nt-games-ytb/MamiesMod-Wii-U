#pragma once

#include "types.hpp"

namespace WiiU {

inline void DCFlushRange(uint32_t address, int32_t size) {
	if(size < 0) {
		return;
	}
	const int32_t count = (size + (address & 0x1F) + 0x1F) * 32;
	for(int i=0; i<count; i++) {
		asm volatile("dcbf 0, %0"
			:
			: "r" (address)
			: "r0");
		address += 0x20;
	}
	asm volatile("dcbf 0, %0"
			:
			: "r" (address - 0x20)
			: "r0");
	asm volatile("sync");
	asm volatile("eieio");
}

inline void ICInvalidateRange(uint32_t address, int32_t size) {
	if(size < 0) {
		return;
	}
	const int32_t count = (size + (address & 0x1F) + 0x1F) * 32;
	for(int i=0; i<count; i++) {
		asm volatile("icbi 0, %0"
			:
			: "r" (address)
			: "r0");
		address += 0x20;
	}
	asm volatile("sync");
	asm volatile("eieio");
	asm volatile("isync");
}

}