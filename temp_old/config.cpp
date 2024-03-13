#include "../mamiesmod.h"

static int split_string(const char *string, char splitChar, char *left, char *right, int size)
{
    int cnt = 0;
    char *writePtr = left;

    while (*string != '\0' && *string != '\n' && *string != '\r' &&
    *string != splitChar && (cnt+1) < size)
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

void default_config(config_t *config)
{
    config->language = 1;
    config->version = 1;
    config->region = 0;
}

int read_config(config_t * config)
{
    FILE *pFile = fopen(CONFIG_PATH, "rb");
    if(!pFile)
        return -1;

    char option[512];
    char value[512];
    char line[1024];

    while (fgets(line, sizeof(line), pFile) != 0)
    {
        if (line[0] == '#' || line[0] == '[')
            continue;

        if (split_string(line, '=', option, value, sizeof(option)) == 1)
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

int write_config(config_t * config)
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
