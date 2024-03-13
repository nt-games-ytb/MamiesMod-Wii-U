#ifndef __FISHING_HOOK_H__
#define __FISHING_HOOK_H__

#include "library/types.hpp"
#include "library/shared_ptr.hpp"
#include "minecraft/entity/Entity.h"
#include "minecraft/entity/player/Player.h"

namespace link {
    static const uint32_t getOwner__11FishingHookFv = 0x0241F684;
}

class FishingHook {
public:

    boost::shared_ptr<mc::Player> getOwner() {
        boost::shared_ptr<mc::Player> player;
        ((void(*)(FishingHook*, boost::shared_ptr<mc::Player>*))link::getOwner__11FishingHookFv)
        (this, &player);
        return player;
    }

};

#endif