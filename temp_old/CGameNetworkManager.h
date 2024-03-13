#pragma once

#include "library/types.hpp"

namespace link {
    static const uint32_t JoinGame__19CGameNetworkManagerFP17FriendSessionInfoib = 0x02D57558;
    static const uint32_t IsHost__19CGameNetworkManagerFv                        = 0x02d54bd4;
}

class CGameNetworkManager {
public:

    static inline CGameNetworkManager *GetNetworkManager() {
        return (CGameNetworkManager*)0x109f83fc;
    }

    bool IsHost() {
        return ((bool(*)(CGameNetworkManager*))link::IsHost__19CGameNetworkManagerFv)
        (this);
    }

};