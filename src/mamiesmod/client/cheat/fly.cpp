/*
** EPITECH PROJECT, 2024
** MamiesMod-Wii-U
** File description:
** The fly.c
*/

#include "../mamiesmod_client.hpp"

void fly(void) {
    static bool enabled = false;

    enabled = !enabled;
    if (enabled) {
        //add_notification(L"Fly", L"Fly enabled", 0xFF00FF00, 0xFFFFFFFF, 2.0f, 0.5f);
    } else {
        //add_notification(L"Fly", L"Fly disabled", 0xFFFF0000, 0xFFFFFFFF, 2.0f, 0.5f);
    }
}