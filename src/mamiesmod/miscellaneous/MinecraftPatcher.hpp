#ifndef MML_MinecraftPatcher_H_
#define MML_MinecraftPatcher_H_

#include <cstdlib>

#define BRANCH_MAX_DISTANCE_POSITIVE 0x1FFFFFC
#define BRANCH_MAX_DISTANCE_NEGATIVE (-0x2000000)

#define INSTRUCTION_BRANCH 0x48000000
#define INSTRUCTION_BRANCH_OFFSET_BIT 0x3FFFFFC

class MinecraftPatcher {
public:
    void patchFunctions();

    static MinecraftPatcher *getInstance() {
        if(!MinecraftPatcher::instance) {
            MinecraftPatcher::instance = new MinecraftPatcher();
        }
        
        return MinecraftPatcher::instance;
    }

    static void destroyInstance() {
        if(MinecraftPatcher::instance) {
            delete MinecraftPatcher::instance;
            MinecraftPatcher::instance = nullptr;
        }
    }

    static void *replaceFunction(void *original_func, void *my_func);
    static void injectInstruction(void *dest, void *instruction, std::size_t instr_size);

private:
    bool patchedFunctions = false;

    static MinecraftPatcher *instance;
    static char executable_buffer[sizeof(int) * 1024];
    static char * executable_buffer_begin;
};

#endif