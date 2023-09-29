#include "tcpgecko/main.h"
#include "tcpgecko/title.h"
#include "dynamic_libs/socket_functions.h"
#include "dynamic_libs/gx2_functions.h"
#include "utils/logger.h"
#include "tcpgecko/tcp_gecko.h"
#include "common/common.h"
#include "cfw_config.h"

int entry() {
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

	cfw_config_t config;

	return Menu_Main(&config);
}

int __entry_menu(int argc, char **argv) {
	return entry();
}