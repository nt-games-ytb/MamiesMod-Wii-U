/*
** MAMIESMOD PROJECT
** MamiesMod-Wii-U
** File description:
** The in_world.cpp
*/

#include "mamiesmod_client.hpp"

void help(void)
{
    static float text_size = 1.0f;
    static float text_x = 200.0f;
    static float text_y = 200.0f;
    static float box_width = 10.0f;
    static float box_height = 10.0f;
    static float box_x = 100.0f;
    static float box_y = 100.0f;
    static uint32_t color = 0xFFFFFFFF;

    if (Key::getPushedKey() & Key::A &&Key::getPushedKey() & Key::Up)
        text_y -= 1.0f;
    if (Key::getPushedKey() & Key::A &&Key::getPushedKey() & Key::Down)
        text_y += 1.0f;
    if (Key::getPushedKey() & Key::A &&Key::getPushedKey() & Key::Left)
        text_x -= 1.0f;
    if (Key::getPushedKey() & Key::A &&Key::getPushedKey() & Key::Right)
        text_x += 1.0f;
    if (Key::getPushedKey() & Key::X &&Key::getPushedKey() & Key::Up)
        text_size += 0.1f;
    if (Key::getPushedKey() & Key::X &&Key::getPushedKey() & Key::Down)
        text_size -= 0.1f;
    if (Key::getPushedKey() & Key::X &&Key::getPushedKey() & Key::Left)
        color += 1;
    if (Key::getPushedKey() & Key::X &&Key::getPushedKey() & Key::Right)
        color -= 1;
    if (Key::getPushedKey() & Key::Y &&Key::getPushedKey() & Key::Up)
        box_height += 1.0f;
    if (Key::getPushedKey() & Key::Y &&Key::getPushedKey() & Key::Down)
        box_height -= 1.0f;
    if (Key::getPushedKey() & Key::Y &&Key::getPushedKey() & Key::Left)
        box_width -= 1.0f;
    if (Key::getPushedKey() & Key::Y &&Key::getPushedKey() & Key::Right)
        box_width += 1.0f;
    if (Key::getPushedKey() & Key::B &&Key::getPushedKey() & Key::Up)
        box_y -= 1.0f;
    if (Key::getPushedKey() & Key::B &&Key::getPushedKey() & Key::Down)
        box_y += 1.0f;
    if (Key::getPushedKey() & Key::B &&Key::getPushedKey() & Key::Left)
        box_x -= 1.0f;
    if (Key::getPushedKey() & Key::B &&Key::getPushedKey() & Key::Right)
        box_x += 1.0f;

    wchar_t info[1000];
    swprintf(info, 1000, L"Text size: %.3f, Text x: %.3f, Text y: %.3f, Box width: %.3f, Box height: %.3f, Box x: %.3f, Box y: %.3f, Color: %x", text_size, text_x, text_y, box_width, box_height, box_x, box_y, color);
    misc::GUI::drawRoundedBox(box_x, box_y, box_width, box_height, 1.0f, color, 0xFF, 5.0f);
    misc::GUI::DisplayText(menu.font, L"Help", text_size, text_x, text_y, color, true);
    misc::GUI::DisplayText(menu.font, info, 2.0f, 1.0f, 20.0f, color, true);
}

void in_world(void)
{
    menu.font = mc::Minecraft::getInstance()->defaultFonts;
    misc::GUI::DisplayText(menu.font, L"MamiesModClient in world", 2.0f, 1.0f, 1.0f, 0xFFFFFFFF, true);
    default_display_coordinates();
    check_menu_status();
    always_display();
    help();
    if (Key::getPushedKey() & Key::ZR) {
        add_notification(L"Test", L"Message", white, white, 10, 10);
    }
    if (Key::getPushedKey() & Key::ZL) {
        update_notifications();
    }
}