#pragma once

#include "../../miscellaneous/code/code.hpp"

#include "ePARTICLE_TYPE.hpp"

namespace mc {
    class ParticleType {
    public:
        static ParticleType* byId(ePARTICLE_TYPE type) {
            return code::Func<ParticleType*, 0x26D9A54, ePARTICLE_TYPE>()(type);
        }
    };
}