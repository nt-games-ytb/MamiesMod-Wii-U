#pragma once

#include "Entity.hpp"

namespace mc {
    class SpectralArrow : public Entity {
    public:
        static uint64_t GetType() {
            return code::Func<uint64_t, 0x0297dbd0>()();
        }
    };
}