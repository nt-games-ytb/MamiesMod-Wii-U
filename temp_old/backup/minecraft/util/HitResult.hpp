#pragma once

#include "../../miscellaneous/code/code.hpp"

#include "../client/resource/shared_ptr.hpp"
#include "BlockPos.hpp"

namespace mc {
    class HitResult {
    public:
        HitResult(const mc_boost::shared_ptr<struct Entity>& entity) {
            code::Func<void, 0x024F3DAC, HitResult*, const mc_boost::shared_ptr<struct Entity>&>()(this, entity);
        }

        mc::BlockPos pos;
        uint32_t field_0xC;
        uint32_t field_0x10;
        struct AABB* aabb;
        uint32_t field_0x18;
        uint32_t field_0x1C;
    };
}