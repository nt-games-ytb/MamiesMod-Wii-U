#ifndef MML_MINECRAFTDATAPROVIDER_H_
#define MML_MINECRAFTDATAPROVIDER_H_

#include <cstddef>

#define MINECRAFT_EXECUTABLE_SPACE_START (0x0384CC20 + 0x10000)
#define MINECRAFT_NEW_OPERATOR_FUNCITON 0x00000000

class MinecraftDataProvider {
public:
    void * allocateExecutable(size_t size);
    void * allocateData(size_t size);

    static MinecraftDataProvider * getInstance() {
        if(!MinecraftDataProvider::instance) {
            MinecraftDataProvider::instance = new MinecraftDataProvider();
        }

        return MinecraftDataProvider::instance;
    }

    static void destroyInstance() {
        if(MinecraftDataProvider::instance) {
            delete MinecraftDataProvider::instance;
            MinecraftDataProvider::instance = NULL;
        }
    }

private:
    int current_executable_space = MINECRAFT_EXECUTABLE_SPACE_START;

    static MinecraftDataProvider * instance;
};

#endif