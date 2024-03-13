#pragma once

#include "mem.hpp"
#include "Func.hpp"
#include "startup.hpp"
#include "Random.hpp"

//#include "tcpgecko.h"
#include "wups.hpp"

namespace code {
	/*void init() {
	    InitTCPGecko();
	    InitWups();
	
	    // Remove Whatever you don't need (Will Reduce File Size)
	    InitSocketFunctionPointers();
	    InitKernelFunctionPointers();
	    InitVPadFunctionPointers();
	    InitMemoryFunctionPointers();
	    InitOSFunctionPointers();
	    InitGX2FunctionPointers();
	    InitLibCurlFunctionPointers();
	
	    memoryInitialize();
	}*/
}

#define WIDTH 1280 //640 * 2
#define HEIGHT 720 //360 * 2

#define MC_CHECK_SIZE(type, size) static_assert(sizeof(mc::type) == size, #type " has invalid size.")

#define MC_VFUNC(return_type, class_type, function_name, ...)     \
	int flag_##function_name;                                     \
	return_type(*function_name)(class_type* _this, ##__VA_ARGS__)

#define DEFINE_STATIC_DEF_VAR(type, name, addr) \
	static inline type default_##name = (type) addr;

#define DEFINE_STATIC_VAR(type, name, addr) \
	static inline type name = (type) addr;
