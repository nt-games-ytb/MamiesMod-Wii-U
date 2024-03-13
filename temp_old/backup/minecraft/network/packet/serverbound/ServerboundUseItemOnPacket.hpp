#pragma once

#include "../../../../miscellaneous/code/code.hpp"

#include "../Packet.hpp"

#include "../../../util/BlockPos.hpp"
#include "../../../util/InteractionHand.hpp"

namespace mc {
    class ServerboundUseItemOnPacket : public Packet {
    public:
        // ServerboundUseItemOnPacket::ServerboundUseItemOnPacket(const BlockPos&, const struct Direction*, InteractionHand::EInteractionHand, float, float, float)
        ServerboundUseItemOnPacket(const BlockPos& pos, const struct Direction* dir, InteractionHand::EInteractionHand hand, float unk1, float unk2, float unk3) {
            code::Func<void, 0x28B25B8, ServerboundUseItemOnPacket*, const BlockPos&, const struct Direction*, InteractionHand::EInteractionHand, float, float, float>()(this, pos, dir, hand, unk1, unk2, unk3);
        }
    
        uint32_t field_0x10;
        uint32_t field_0x14;
        BlockPos position;
        struct Direction* direction;
        InteractionHand::EInteractionHand e_hand;
        float clickX;
        float clickY;
        float clickZ;
    };
}