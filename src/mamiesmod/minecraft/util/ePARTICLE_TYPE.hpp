#pragma once

namespace mc {
    enum ePARTICLE_TYPE : int {
        NONE = 0, SMOKE = 1, NOTE = 2, PORTAL = 3, EXPLODE = 5, FLAME = 6, 
        LAVA = 7, FOOTSTEP = 8, DROPLET = 9, LARGE_SMOKE = 10, RED_DUST = 11,
        SNOWBALL_POOF = 12, SNOW_SHOVEL = 13, SLIME = 14, HEART = 15, DEPTH_SUSPEND = 17, 
        CRITICAL_HIT = 18, HUGE_EXPLOSION = 19, LARGE_EXPLODE = 20, TOWN_AURA = 21,
        SPELL = 22, WITCH_MAGIC = 23, MOB_SPELL = 24, MOB_SPELL_AMBIANT = 25, DRIP_WATER = 27, 
        DRIP_LAVA = 28, ENCHANTMENT_TABLE = 29, ANGRY_VILLAGER = 31, HAPPY_VILLAGER = 32, 
        FIREWORKS_SPARK = 33, WAKE = 34, INSTANT_SPELL = 36, CLOUD = 37, BARRIER = 38, ICON_CRACK = 39, 
        BLOCK_DUST = 40, SPLASH = 41, DRAGON_BREATH = 44, END_ROD = 45, BLACK_HEART = 46, 
        FALLING_DUST = 48, TOTEM = 49, SPIT = 51,
    }; 
}