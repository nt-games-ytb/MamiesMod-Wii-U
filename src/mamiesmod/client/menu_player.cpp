/*
** EPITECH PROJECT, 2024
** MamiesMod-Wii-U
** File description:
** The menu_player.c
*/

#include "mamiesmod_client.hpp"

void display_player_other_tab(void)
{
    static cheat_t cheat_list[] = {
        {L"Fly", &fly, toggle, false},
        {L"a", &fly, toggle, false},
        {L"b", &fly, toggle, false},
        {L"c", &fly, toggle, false},
        {L"d", &fly, toggle, false},
        {L"e", &fly, toggle, false},
        {L"f", &fly, toggle, false},
        {L"g", &fly, toggle, false},
        {L"h", &fly, toggle, false},
        {L"i", &fly, toggle, false},
        {L"j", &fly, toggle, false},
        {L"k", &fly, toggle, false},
        {L"l", &fly, toggle, false},
        {L"m", &fly, toggle, false},
        {L"n", &fly, toggle, false},
        {L"o", &fly, toggle, false},
        {L"p", &fly, toggle, false}
    };

    static int cheat_number = 2;
    static int index = 0;
    static int cursor = 0;
    static bool changed = false;
    wchar_t text[105];
    uint32_t color;

    if (Key::getPushedKey() & Key::Up) {
        if (changed == false) {
            if (index == 0 && cursor == 0) {
                for (int i = 10; i > 0; i--) {
                    if (cheat_number - i >= 0) {
                        index = cheat_number - i;
                        cursor = i - 1;
                        break;
                    }
                }
                //index = cheat_number;
                //cursor = ((index > 9) ? 10 : index);
            } else if (cursor == 0) {
                index--;
            } else {
                cursor--;
            }
        }
        changed = true;
    } else if (Key::getPushedKey() & Key::Down) {
        if (changed == false) {
            if (index == cheat_number - 1 || cursor == cheat_number - 1 ||
            index + cursor == cheat_number - 1) {
                index = 0;
                cursor = 0;
            } else if (cursor == 10) {
                index++;
            } else {
                cursor++;
            }
        }
        changed = true;
    } else {
        changed = false;
    }

    if (Key::getPushedKey() & Key::Right) {
        if (menu.tab_changed == false)
            cheat_list[index + cursor].enabled = !cheat_list[index + cursor].enabled;
            cheat_list[index + cursor].cheat_function();
        menu.tab_changed = true;
    } else if (Key::getPushedKey() & Key::Left) {
        if (menu.tab_changed == false) {
            menu.player_tab_index = 0;
            menu.menu_tab_index = 1;
        }
        menu.tab_changed = true;
    } else {
        menu.tab_changed = false;
    }

    for (int i = index; i < index + 10; i++) {
        if (i >= cheat_number)
            break;
        if (cheat_list[i].type == toggle) {
            if (cheat_list[i].enabled) {
                color = get_text_color(i - index, cursor, green_on, green_off);
            } else {
                color = get_text_color(i - index, cursor, red_on, red_off);
            }
        } else {
            color = get_text_color(i - index, cursor, white, grey);
        }
        mc_swprintf(text, 105, L"   %ls", cheat_list[i].name);
        misc::GUI::DisplayText(menu.font, text, 3.0f, 990.0f, 200.0f + ((i - index) * 30), color, false);
    }
    mc_swprintf(text, 105, L"Index: %d, Cursor: %d", index, cursor);
    misc::GUI::DisplayText(menu.font, text, 3.0f, 1.0f, 230.0f, 0xFFFFFFFF, true);
}

void display_player_visual_tab(void)
{
    return;
}

void display_player_settings_tab(void)
{
    return;
}

void display_player_pvp_tab(void)
{
    return;
}

void display_player_tab(void)
{
    static int index = 1;
    static bool changed = false;

    if (Key::getPushedKey() & Key::Up) {
        if (changed == false)
            index = ((index - 1) <= 0) ? 4 : index - 1;
        changed = true;
    } else if (Key::getPushedKey() & Key::Down) {
        if (changed == false)
            index = ((index + 1) >= 5) ? 1 : index + 1;
        changed = true;
    } else {
        changed = false;
    }

    if (Key::getPushedKey() & Key::Right) {
        if (menu.tab_changed == false)
            menu.player_tab_index = index;
        menu.tab_changed = true;
    } else if (Key::getPushedKey() & Key::Left) {
        if (menu.tab_changed == false) {
            menu.player_tab_index = 0;
            menu.menu_tab_index = 0;
        }
        menu.tab_changed = true;
    } else {
        menu.tab_changed = false;
    }

    misc::GUI::DisplayText(menu.font, L"< Other", 3.0f,
        990.0f, element_1_pos_y, get_text_color(1, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L"< Visual", 3.0f,
        990.0f, element_2_pos_y, get_text_color(2, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L"< Settings in game", 3.0f,
        990.0f, element_3_pos_y, get_text_color(3, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L"< PvP", 3.0f,
        990.0f, element_4_pos_y, get_text_color(4, index, white, grey), false);

    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_1_pos_y, get_text_color(1, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_2_pos_y, get_text_color(2, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_3_pos_y, get_text_color(3, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_4_pos_y, get_text_color(4, index, white, grey), false);
}
