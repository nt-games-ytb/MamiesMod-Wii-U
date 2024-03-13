#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>
#include "../dynamic_libs/os_functions.h"
#include "../dynamic_libs/fs_functions.h"
#include "../dynamic_libs/sys_functions.h"
#include "../dynamic_libs/vpad_functions.h"
#include "../dynamic_libs/socket_functions.h"
#include "../kernel/kernel_functions.h"
#include "../system/memory.h"
#include "../common/common.h"
#include "install.h"
#include "code_handler.h"
#include "../utils/logger.h"
#include "../utils/function_patcher.h"
#include "../patcher/function_patcher_gx2.h"
#include "../patcher/function_patcher_coreinit.h"
#include "sd_ip_reader.h"
#include "title.h"
#include "tcp_gecko.h"
#include "fs/sd_fat_devoptab.h"

bool isCodeHandlerInstalled = false;
bool areSDCheatsEnabled = false;

void applyFunctionPatches() {
	patchIndividualMethodHooks(method_hooks_gx2, method_hooks_size_gx2, method_calls_gx2);
	patchIndividualMethodHooks(method_hooks_coreinit, method_hooks_size_coreinit, method_calls_coreinit);
}

void installCodeHandler() {
	unsigned int physicalCodeHandlerAddress = (unsigned int) OSEffectiveToPhysical((void *) CODE_HANDLER_INSTALL_ADDRESS);
	SC0x25_KernelCopyData((u32) physicalCodeHandlerAddress, (unsigned int) codeHandler, codeHandlerLength);
	DCFlushRange((const void *) CODE_HANDLER_INSTALL_ADDRESS, (u32) codeHandlerLength);
	isCodeHandlerInstalled = true;
}

void install() {
	installCodeHandler();
	initializeUDPLog();
	log_print("Patching functions\n");
	applyFunctionPatches();
}