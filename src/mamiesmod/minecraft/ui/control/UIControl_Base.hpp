#pragma once

#include "../../../miscellaneous/code/code.hpp"

#include "UIControl.hpp"

namespace mc {
    class UIControl_Base : public UIControl {
    public:
        uint8_t _filler[0xC];
    };
}