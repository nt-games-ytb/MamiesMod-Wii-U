#pragma once

#include "../../miscellaneous/code/code.hpp"

#include "../client/resource/shared_ptr.hpp"

namespace mc {
    class DamageSource {
    public:
        static DamageSource* CreatePlayerAttack(const mc_boost::shared_ptr<struct Player>& player) {
            return code::Func<DamageSource*, 0x02252ac4, const mc_boost::shared_ptr<struct Player>&>()(player);
        }
    };
}