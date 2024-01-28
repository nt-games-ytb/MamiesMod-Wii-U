#ifndef _MAIN_H_
#define _MAIN_H_

#include "../common/types.h"
#include "../dynamic_libs/os_functions.h"
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

int Menu_Main(config_t *currentConfig);

extern bool isCodeHandlerInstalled;
extern bool areSDCheatsEnabled;
extern bool MamiesModClient;

#ifdef __cplusplus
}
#endif

#endif