/*
** MAMIESMOD PROJECT
** MamiesMod-Wii-U
** File description:
** The mamiesmod_app.h
*/

#pragma region Includes
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "../common/common.h"

#include "../dynamic_libs/os_functions.h"
#include "../dynamic_libs/fs_functions.h"
#include "../dynamic_libs/sys_functions.h"
#include "../dynamic_libs/vpad_functions.h"
#include "../dynamic_libs/socket_functions.h"

#include "../fs/sd_fat_devoptab.h"
#include "../fs/fs_utils.h"

#include "../kernel/kernel_functions.h"

#include "../system/memory.h"

#include "../tcpgecko/tcp_gecko.h"
#pragma endregion Includes

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAMIESMOD_APP_H_
    #define MAMIESMOD_APP_H_

#pragma region App config
    #define APP_PATH            "sd:/wiiu/apps/MamiesMod Wii U"
    #define CONFIG_PATH         (APP_PATH "/config.ini")

typedef struct config_s {
    int language;
    int version;
    int region;
} config_t;

void default_config(config_t *config);
int read_config(config_t *config);
int write_config(config_t *config);
#pragma endregion App config

typedef enum {
    EXIT,
    TCP_GECKO
} LaunchMethod;

extern bool MamiesModClient;

int app_menu(void);
int mamiesmod_thread(int argc, void* argv);


#endif /* MAMIESMOD_APP_H_ */

#ifdef __cplusplus
}
#endif