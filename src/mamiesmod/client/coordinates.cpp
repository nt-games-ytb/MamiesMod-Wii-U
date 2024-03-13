/*
** EPITECH PROJECT, 2024
** MamiesMod-Wii-U
** File description:
** The coordinates.cpp
*/

#include "mamiesmod_client.hpp"

void test(void)
{
    /*mc::ConsoleUIController* controller = mc::ConsoleUIController::getInstance();
    controller->PlayUISFX(mc::SoundEvent::random_fuse);*/

    mc::LocalPlayer* player = mc::Minecraft::getInstance()->thePlayer;
    player->playSound(mc::SoundEvent::random_fuse, 100.0f, 1.0f);
}

void display_coordinates(float size, float x, float y, uint precision, uint32_t color = 0xFFFFFFFF)
{
    mc::LocalPlayer* player = mc::Minecraft::getInstance()->thePlayer;
    wchar_t tmp[20];
    wchar_t coordinates_text[64];

    if (precision > 9)
        precision = 9;
    swprintf(tmp, 20, L"(%%.%df, %%.%df, %%.%df)", precision, precision, precision);
    swprintf(coordinates_text, 64, tmp, player->position.x, player->position.y, player->position.z);
    int text_width = menu.font->width(coordinates_text) / 2;
    misc::GUI::DisplayText(menu.font, coordinates_text, size, x - text_width, y, color);
}

void default_display_coordinates(void)
{
    display_coordinates(2.5, WIDTH / 2 - 100, 5.0, 3);
}