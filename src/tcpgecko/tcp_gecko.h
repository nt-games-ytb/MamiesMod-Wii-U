#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define DATA_BUFFER_SIZE 0x5000

int mamiesmod_thread(int argc, void* argv);
void install(void);
void startTCPGecko(void);

#ifdef __cplusplus
}
#endif