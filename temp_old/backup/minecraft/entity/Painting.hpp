#pragma once

#include "Entity.hpp"

namespace mc {
    class Painting : public Entity {
    public:
        static uint64_t GetType() {
            return code::Func<uint64_t, 0x027ce9bc>()();
        }
    };
}