#include "tcpgecko/title.h"
#include "dynamic_libs/socket_functions.h"
#include "dynamic_libs/gx2_functions.h"
#include "dynamic_libs/fs_functions.h"
#include "dynamic_libs/os_functions.h"
#include "dynamic_libs/sys_functions.h"
#include "dynamic_libs/vpad_functions.h"
#include "utils/logger.h"
#include "tcpgecko/tcp_gecko.h"
#include "common/common.h"
#include "mamiesmod/mamiesmod_app.h"

int entry(void) {
	if (isRunningAllowedTitleID()) {
		InitOSFunctionPointers();
		InitSysFunctionPointers();
		InitFSFunctionPointers();
		InitVPadFunctionPointers();
		InitSocketFunctionPointers();
		InitGX2FunctionPointers();

		log_init(COMPUTER_IP_ADDRESS);
		log_print("OSGetTitleID checks passed...\n");
		startTCPGecko();

		return EXIT_RELAUNCH_ON_LOAD;
	}

	//! *******************************************************************
	//! *                 Jump to our application                    *
	//! *******************************************************************

	return app_menu();
}

int __entry_menu(int argc, char **argv) {
	return entry();
}