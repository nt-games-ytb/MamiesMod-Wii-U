#pragma once

namespace linkmc {
    static const uint32_t SetAchievementUnlocked__19ConsoleUIControllerFiN3 = 0x02DAAD4C;
    static const uint32_t PlayUISFX__19ConsoleUIControllerFPC10SoundEvent   = 0x02DA7918;
}

#include "../../../miscellaneous/code/code.hpp"
#include "../../util/SoundEvent.hpp"

namespace mc {
    class ConsoleUIController {
    public:
        static inline ConsoleUIController *getInstance() {
            return (ConsoleUIController*)0x109f95e0;
        }

        inline void SetAchievementUnlocked(int32_t unk_i0, int32_t id, int32_t unk_i2, int32_t unk_i3) {
            return ((void(*)(ConsoleUIController*, int32_t, int32_t, int32_t, int32_t))linkmc::SetAchievementUnlocked__19ConsoleUIControllerFiN3)
            (this, unk_i0, id, unk_i2, unk_i3);
        }

        inline void PlayUISFX(mc::SoundEvent *sound) {
            return ((void(*)(ConsoleUIController*, mc::SoundEvent*))linkmc::PlayUISFX__19ConsoleUIControllerFPC10SoundEvent)
            (this, sound);
        }
    };
}