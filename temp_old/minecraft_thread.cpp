/*
** EPITECH PROJECT, 2024
** MamiesMod-Wii-U
** File description:
** The minecraft_thread.c
*/

#include "../mamiesmod.h"

// InGame *_*
void in_game() {
    /*if (!isInitialized) {
        isInitialized = true;
    }
    if (isRenderAllowed)
        MCRender();
    MCGui();*/
}

// NotInGame *_*
void not_in_game() {/*
    isInWorld = false;
    if (!LOADisInitialized) {
        LogServer();
        LOADisInitialized = true;
    }
    MCRenderInMenu();*/
}

int minecraft_thread(int argc, void* argv) {
    uint32_t inject_in_game[4] = {
        0x3D800000 | ((uint32_t)&in_game >> 16),
        0x618C0000 | ((uint32_t)&in_game & 0xFFFF),
        0x7D8903A6,
        0x4E800421
    };

    uint32_t inject_not_in_game[4] = {
        0x3D800000 | ((uint32_t)&not_in_game >> 16),
        0x618C0000 | ((uint32_t)&not_in_game & 0xFFFF),
        0x7D8903A6,
        0x4E800421
    };

    MinecraftPatcher::injectInstruction((void *)0x02D9CAC0, inject_in_game, sizeof(inject_in_game));
    MinecraftPatcher::injectInstruction((void *)0x02D9C8B0, inject_not_in_game, sizeof(inject_not_in_game));

    return 0;
}