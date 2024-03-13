/*
** MAMIESMOD PROJECT
** MamiesMod-Wii-U
** File description:
** The minecraft_thread.c
*/

#include "mamiesmod_client.hpp"
#include "../miscellaneous/code/Random.hpp"

uint32_t code::mLehmer = 0;
uint32_t misc::TextColorIndex = 0;
uint32_t misc::frameCount = 0;

int mamiesmod_thread(int argc, void* argv) {
    uint32_t inject_in_world[4] = {
        0x3D800000 | ((uint32_t)&in_world >> 16),
        0x618C0000 | ((uint32_t)&in_world & 0xFFFF),
        0x7D8903A6,
        0x4E800421
    };

    uint32_t inject_not_in_world[4] = {
        0x3D800000 | ((uint32_t)&not_in_world >> 16),
        0x618C0000 | ((uint32_t)&not_in_world & 0xFFFF),
        0x7D8903A6,
        0x4E800421
    };

    MinecraftPatcher::injectInstruction((void *)0x02D9CAC0, inject_in_world, sizeof(inject_in_world));
    MinecraftPatcher::injectInstruction((void *)0x02D9C8B0, inject_not_in_world, sizeof(inject_not_in_world));

    return 0;
}