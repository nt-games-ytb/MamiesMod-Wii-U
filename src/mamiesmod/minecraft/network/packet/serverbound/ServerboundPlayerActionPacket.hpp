#pragma once

#include "../../../../miscellaneous/code/code.hpp"

#include "../Packet.hpp"

#include "../../../util/BlockPos.hpp"

namespace mc {
    class ServerboundPlayerActionPacket : public Packet {
    public:
        enum Action : int {
            START_BREAKING, STOP_BREAKING, FINISH_BREAKING, DROP_ALL, DROP_SINGLE, RELEASE, SWAP_HANDS
        };

        ServerboundPlayerActionPacket(Action arg2, const BlockPos& pos, const struct Direction* dir, int arg5) {
            code::Func<void, 0x028AEC5C, ServerboundPlayerActionPacket*, Action, const BlockPos&, const struct Direction*, int>()(this, arg2, pos, dir, arg5);
        }

        ServerboundPlayerActionPacket(uint32_t arg2, const BlockPos& pos) {
            uint32_t arg4 = *(uint32_t*) 0x104C24A0;
            code::Func<void, 0x028AEC5C, ServerboundPlayerActionPacket*, uint32_t, const BlockPos&, uint32_t>()(this, arg2, pos, arg4);
        }

        uint32_t field_0x10;
        uint32_t field_0x14;
        BlockPos position;
        struct Direction* direction;
        uint32_t _action;
        uint32_t field_0x2C;
    };
}