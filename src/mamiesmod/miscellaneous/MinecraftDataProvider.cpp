#include "MinecraftDataProvider.hpp"

namespace link {
    static const unsigned int __nw__FUi = 0x0382AACC;
}

MinecraftDataProvider * MinecraftDataProvider::instance = NULL;

void * MinecraftDataProvider::allocateExecutable(size_t size) {
    int ret = current_executable_space;
    current_executable_space += size;
    return (void *)ret;
}

void * MinecraftDataProvider::allocateData(size_t size) {
    return ((void*(*)(unsigned int))link::__nw__FUi)
    ((unsigned int)size);
}