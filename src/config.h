#ifndef CONFIG_H_
#define CONFIG_H_

#define APP_PATH            "sd:/wiiu/apps/MamiesMod Wii U"
#define CONFIG_PATH         (APP_PATH "/config.ini")

#ifdef __cplusplus
extern "C" {
#endif

typedef struct config_s {
    int language;
    int version;
    int region;
} config_t;

void default_config(config_t * config);
int read_config(config_t * config);
int write_config(config_t * config);

#ifdef __cplusplus
}
#endif

#endif // CONFIG_H_