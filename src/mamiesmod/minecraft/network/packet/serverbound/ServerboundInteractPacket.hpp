#pragma once

#include "../../../../miscellaneous/code/code.hpp"

#include "../Packet.hpp"

#include "../../../util/InteractionHand.hpp"

#include "../../../client/resource/shared_ptr.hpp"

namespace mc {
    class ServerboundInteractPacket : public Packet {
    public:
        ServerboundInteractPacket(const mc_boost::shared_ptr<struct Entity>& entity) {
            code::Func<void, 0x028AC244, ServerboundInteractPacket*, const mc_boost::shared_ptr<struct Entity>&>()(this, entity);
        }

        uint32_t field_0x10;
        uint32_t field_0x14;
        uint32_t entityId;
        InteractionHand::EInteractionHand action;
        uint32_t field_0x20;
        uint32_t field_0x24;
    };
}