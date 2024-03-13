#pragma once

#include "../Packet.hpp"
#include "../../../client/resource/wstring.hpp"

namespace mc {
    class ServerboundPreLoginPacket : public Packet {
    public:
        uint32_t unk_0x10;
        uint32_t unk_0x14;
        uint32_t gameVersion;
        mstd::wstring nnid;
    };
}