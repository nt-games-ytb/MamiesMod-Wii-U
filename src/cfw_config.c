/***************************************************************************
 * Copyright (C) 2016
 * by Dimok
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to alter it and
 * redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you
 * must not claim that you wrote the original software. If you use
 * this software in a product, an acknowledgment in the product
 * documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and
 * must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 ***************************************************************************/
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>
#include "cfw_config.h"
#include "fs/fs_utils.h"

static int split_string(const char *string, char splitChar, char *left, char *right, int size)
{
    int cnt = 0;
    char *writePtr = left;

    while(*string != '\0' && *string != '\n' && *string != '\r' && *string != splitChar && (cnt+1) < size)
    {
        *writePtr++ = *string++;
        cnt++;
    }

    *writePtr = 0;
    *right = 0;

    writePtr--;

    // remove trailing spaces
    while(writePtr > left && *writePtr == ' ')
        *writePtr-- = 0;

    if(*string == splitChar)
    {
        string++;
        writePtr = right;

        // skip spaces after split character
        while(*string == ' ')
            string++;

        cnt = 0;
        while(*string != '\0' && *string != '\n' && *string != '\r' && (cnt+1) < size)
        {
            *writePtr++ = *string++;
        }
        *writePtr = 0;
        return 1;
    }
    else
    {
        return -1;
    }
}

void default_config(cfw_config_t * config)
{
    memset(config, 0, sizeof(cfw_config_t));
    config->language = 1;
    config->version = 1;
    config->region = 0;
}

int read_config(cfw_config_t * config)
{
    FILE *pFile = fopen(CONFIG_PATH, "rb"); //Ouvre
    if(!pFile) //Si y'a pas arrête
        return -1;

    char option[64];
    char value[64];
    char line[0x100];

    while(fgets(line, sizeof(line), pFile) != 0)
    {
        if(line[0] == '#' || line[0] == '[')
            continue;

        if(split_string(line, '=', option, value, sizeof(option)) == 1)
        {
            if(strcmp(option, "language") == 0)
                config->language = atoi(value);
            else if(strcmp(option, "version") == 0)
                config->version = atoi(value);
            else if(strcmp(option, "region") == 0)
                config->region = atoi(value);
        }
    }

    fclose(pFile);
    return 0;
}

int write_config(cfw_config_t * config)
{
    CreateSubfolder(APP_PATH);

    FILE *pFile = fopen(CONFIG_PATH, "wb");
    if(!pFile)
        return -1;

    fprintf(pFile, "[MamiesMod Wii U]\n");
    fprintf(pFile, "language=%i\n", config->language);
    fprintf(pFile, "version=%i\n", config->version);
    fprintf(pFile, "region=%i\n", config->region);
    fclose(pFile);
    return 0;
}
