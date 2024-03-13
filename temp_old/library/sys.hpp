#ifndef __SYS_H__
#define __SYS_H__

#include "types.hpp"

inline uint64_t getTitleId() {
    return *(uint64_t*)0x10013C10;
}

#endif