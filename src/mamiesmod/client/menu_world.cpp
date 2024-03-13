/*
** EPITECH PROJECT, 2024
** MamiesMod-Wii-U
** File description:
** The menu_world.c
*/

#include "mamiesmod_client.hpp"

void display_world_options_tab(void)
{
    return;
}

void display_world_generation_tab(void)
{
    return;
}

void display_world_entities_tab(void)
{
    return;
}

void display_world_liquids_tab(void)
{
    return;
}

void display_world_infinite_tab(void)
{
    return;
}

void display_world_enchant_tab(void)
{
    return;
}

void display_world_other_tab(void)
{
    return;
}

void display_world_tab(void)
{
    static int index = 1;
    static bool changed = false;

    if (Key::getPushedKey() & Key::Up) {
        if (changed == false)
            index = ((index - 1) <= 0) ? 7 : index - 1;
        changed = true;
    } else if (Key::getPushedKey() & Key::Down) {
        if (changed == false)
            index = ((index + 1) >= 8) ? 1 : index + 1;
        changed = true;
    } else {
        changed = false;
    }

    if (Key::getPushedKey() & Key::Right) {
        if (menu.tab_changed == false)
            menu.world_tab_index = index;
        menu.tab_changed = true;
    } else if (Key::getPushedKey() & Key::Left) {
        if (menu.tab_changed == false) {
            menu.world_tab_index = 0;
            menu.menu_tab_index = 0;
        }
        menu.tab_changed = true;
    } else {
        menu.tab_changed = false;
    }

    misc::GUI::DisplayText(menu.font, L"< World options", 3.0f,
        990.0f, element_1_pos_y, get_text_color(1, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L"< World generation", 3.0f,
        990.0f, element_2_pos_y, get_text_color(2, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L"< Entities", 3.0f,
        990.0f, element_3_pos_y, get_text_color(3, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L"< Liquids", 3.0f,
        990.0f, element_4_pos_y, get_text_color(4, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L"< Infinite", 3.0f,
        990.0f, element_5_pos_y, get_text_color(5, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L"< Enchant", 3.0f,
        990.0f, element_6_pos_y, get_text_color(6, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L"< Other", 3.0f,
        990.0f, element_7_pos_y, get_text_color(7, index, white, grey), false);

    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_1_pos_y, get_text_color(1, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_2_pos_y, get_text_color(2, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_3_pos_y, get_text_color(3, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_4_pos_y, get_text_color(4, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_5_pos_y, get_text_color(5, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_6_pos_y, get_text_color(6, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_7_pos_y, get_text_color(7, index, white, grey), false);
}