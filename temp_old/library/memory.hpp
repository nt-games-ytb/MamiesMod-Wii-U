#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "types.hpp"

namespace link {
	static const uint32_t XMemCpy__FPvPCvUi = 0x030E2228;
	static const uint32_t XMemSet__FPviUi   = 0x030E2238;
	static const uint32_t _memcpy           = 0x0384C758;
	static const uint32_t _memset           = 0x0384C768;
	static const uint32_t _memcmp           = 0x020B9CBC;
	static const uint32_t __nw__FUi         = 0x0382AACC;
	static const uint32_t __dl__FPv         = 0x0382ABB4;
	static const uint32_t __vec_new         = 0x0382A1AC;
	static const uint32_t __ghs_strcpy      = 0x0382CB58;
}

namespace mem {
	inline void WriteUInt(uint32_t address, uint32_t value) {
		*(uint32_t*)address = value;
	}

	inline uint32_t ReadUInt(uint32_t address) {
		return *(uint32_t*)address;
	}

	inline void XMemCpy(void *unk_v0, const void *unk_v1, uint32_t length) {
		return ((void(*)(void*, const void*, uint32_t))link::XMemCpy__FPvPCvUi)
		(unk_v0, unk_v1, length);
	}

	inline void XMemSet(void *unk_v0, int32_t value, uint32_t length) {
		return ((void(*)(void*, int32_t, uint32_t))link::XMemSet__FPviUi)
		(unk_v0, value, length);
	}

	inline void memcpy(void *unk_v0, void *value, uint32_t length) {
		return ((void(*)(void*, void*, uint32_t))link::_memcpy)
		(unk_v0, value, length);
	}

	inline void memset(void *unk_v0, int32_t value, uint32_t length) {
		return ((void(*)(void*, int32_t, uint32_t))link::_memset)
		(unk_v0, value, length);
	}

	inline int32_t memcmp(const void *buf1, const void *buf2, unsigned int n) {
		return ((int32_t(*)(const void*, const void*, unsigned int))link::_memcmp)
		(buf1, buf2, n);
	}
	
	inline void *malloc(uint32_t size) {
		return ((void*(*)(uint32_t))link::__nw__FUi)
		(size);
	}

	inline void free(void *ptr) {
		return ((void(*)(void*))link::__dl__FPv)
		(ptr);
	}

	inline void __vec_new(void *startAddr, int32_t elementsCount, int32_t elementSize, void *constructorFunction) {
		return ((void(*)(void*, int32_t, int32_t, void*))link::__vec_new)
		(startAddr, elementsCount, elementSize, constructorFunction);
	}

	inline void strcpy(char *str_0, char *str_1) {
		return ((void(*)(char*, char*))link::__ghs_strcpy)
		(str_0, str_1);
	}

}

#endif