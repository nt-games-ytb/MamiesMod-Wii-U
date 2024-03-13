#pragma once

#include <cstdint>

#define PUSHED_KEY_ID *(uint32_t*)0x102EFA66
#define SCREEN_TOUCHED *(int*)0x102EF954

class Key {
public:
    static uint32_t getPushedKey();

    static const uint32_t
        TV = 0x1,
        R_Stick_Pushed = 0x2,
        L_Stick_Pushed = 0x4,
        HomeButton = 0x20000,
        Minus = 0x40000,
        Plus = 0x80000,
        R = 0x100000,
        L = 0x200000,
        ZR = 0x400000,
        ZL = 0x800000,
        Down = 0x1000000,
        Up = 0x2000000,
        Right = 0x4000000,
        Left = 0x8000000,
        Y = 0x10000000,
        X = 0x20000000,
        B = 0x40000000,
        A = 0x80000000;
};

