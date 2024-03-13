#pragma once

#include "../../../miscellaneous/code/code.hpp"

#include "../../client/resource/shared_ptr.hpp"
#include "../../util/BlockPos.hpp"

namespace mc {
    class ServerPlayerGameMode {
    public:
        void getServerPlayer(const mc_boost::shared_ptr<struct ServerPlayer>& player) {
            code::Func<void, 0x032DE5D8, ServerPlayerGameMode*, const mc_boost::shared_ptr<struct ServerPlayer>&>()(this, player);
        }

        static code::Func<void, 0x032de9d8, ServerPlayerGameMode*, const BlockPos&> _destroyBlock;
        void destroyBlock(const mc::BlockPos& pos) {
            _destroyBlock(this, pos);
        }
    };
}