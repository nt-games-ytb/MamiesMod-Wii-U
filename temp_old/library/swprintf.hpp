#ifndef __SWPRINTF_H__
#define __SWPRINTF_H__

#include "types.hpp"
#include "basic_string.hpp"
#include "../minecraft/client/Minecraft.h"
#include "../minecraft/network/packet/clientbound/ClientboundChatPacket.h"
#include "../minecraft/network/listener/ClientPacketListener.h"
/*

template <typename ... Args>
inline void log(std::basic_string<wchar_t> wcstr, Args ... args) {
    wchar_t result[100];
    swprintf(result, 100, wcstr.c_str(), args ...);
    if (mc::Minecraft::getInstance()->thePlayer != nullptr) {
        std::basic_string<wchar_t> wcstr = result;
        boost::shared_ptr<ClientboundChatPacket> packet(ClientboundChatPacket::Ctor(nullptr, wcstr, ClientboundChatPacket::EChatPacketMessage::unk_0, 0));
        mc::Minecraft::getInstance()->thePlayer->listener->handleChat(packet);
    }
}*/

#endif