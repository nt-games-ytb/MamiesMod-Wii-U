#pragma once

#include "../../../miscellaneous/code/code.hpp"

namespace mc {
    class MobEffect {
    public:
        static MobEffect* byId(int id) {
            return code::Func<MobEffect*, 0x026907a4, int>()(id);
        }

        int getId() {
            return code::Func<int, 0x026907c0, MobEffect*>()(this);
        }
    };
}