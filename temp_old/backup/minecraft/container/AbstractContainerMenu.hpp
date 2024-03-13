#pragma once

#include "../../miscellaneous/code/code.hpp"

#include "../client/resource/shared_ptr.hpp"
#include "../client/resource/vector.hpp"

namespace mc {
    class AbstractContainerMenu {
    public:
        mstd::vector<mc_boost::shared_ptr<struct ItemInstance>>& getItems() {
            return code::Func<mstd::vector<mc_boost::shared_ptr<struct ItemInstance>>&, 0x02033EA0, AbstractContainerMenu*>()(this);
        }  
    };
}