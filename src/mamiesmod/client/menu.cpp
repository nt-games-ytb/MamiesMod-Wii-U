/*
** EPITECH PROJECT, 2024
** MamiesMod-Wii-U
** File description:
** The minecraft_menu.c
*/

#include "mamiesmod_client.hpp"

void check_menu_status(void)
{
    static bool changed = false;

    if (!menu.opened && Key::getPushedKey() & Key::L && Key::getPushedKey() & Key::R) {
        if (changed)
            return;
        menu.opened = true;
        changed = true;
        return;
    }
    if (menu.opened && Key::getPushedKey() & Key::L && Key::getPushedKey() & Key::R) {
        if (changed)
            return;
        menu.opened = false;
        changed = true;
        return;
    }
    changed = false;
}

void always_display(void)
{
    misc::GUI::DisplayText(menu.font, L"Press L + R to open/close the menu", 2.0f, 800.0f, 660.0f, 0xffffffff, true);
    if (menu.opened)
        display_menu();
}

uint32_t get_text_color(int id, int index, uint32_t enable, uint32_t disable)
{
    if (id == index)
        return enable;
    return disable;
}

uint32_t get_multiple_text_color(int id, int index[], uint32_t enable, uint32_t disable)
{
    for (int i = 0; index[i] != 0; i++) {
        if (id == index[i])
            return enable;
    }
    return disable;
}

void display_menu_tab(void)
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
            menu.menu_tab_index = index;
        menu.tab_changed = true;
    } else {
        menu.tab_changed = false;
    }

    misc::GUI::DisplayText(menu.font, L"   Player", 3.0f,
         990.0f, element_1_pos_y, get_text_color(1, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L"   World", 3.0f,
         990.0f, element_2_pos_y, get_text_color(2, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L"   Minigames", 3.0f,
         990.0f, element_3_pos_y, get_text_color(3, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L"   Nicknames", 3.0f,
         990.0f, element_4_pos_y, get_text_color(4, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L"   Build", 3.0f,
         990.0f, element_5_pos_y, get_text_color(5, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L"   Other", 3.0f,
         990.0f, element_6_pos_y, get_text_color(6, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L"   Settings", 3.0f,
         990.0f, element_7_pos_y, get_text_color(7, index, white, grey), false);

    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_1_pos_y, get_text_color(1, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_2_pos_y, get_text_color(2, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_3_pos_y, get_text_color(3, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_4_pos_y, get_text_color(4, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_5_pos_y, get_text_color(5, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_6_pos_y, get_text_color(6, index, white, grey), false);
    misc::GUI::DisplayText(menu.font, L">", 3.0f, 1240.0f, element_7_pos_y, get_text_color(7, index, white, grey), false);
}

void display_menu(void)
{
    misc::GUI::renderSetup();
    misc::GUI::drawRoundedBox(menu.position_x, menu.position_y, 300, 435, 15, menu.color, (menu.opacity / 100) * 255, 15);
    misc::GUI::DisplayText(menu.font, L"MamiesModClient", 4.0f, 980.0f, 145.0f, white, false);

    misc::GUI::DisplayText(menu.font, L"Move up", 1.75f, 1000.0f, 565.0f, white, true);
    misc::GUI::DisplayText(menu.font, L"|", 1.75f, 1035.0f, 585.0f, white, true);
    misc::GUI::DisplayText(menu.font, L"Move left -+- Move right / Enable & Disable", 1.75f, 948.0f, 600.0f, white, true);
    misc::GUI::DisplayText(menu.font, L"|", 1.75f, 1035.0f, 615.0f, white, true);
    misc::GUI::DisplayText(menu.font, L"Move down", 1.75f, 995.0f, 635.0f, white, true);

    static void (*menu_tab[])(void) = {
        &display_menu_tab,
        &display_player_tab,
        &display_world_tab,
        &display_minigames_tab,
        &display_nicknames_tab,
        &display_build_tab,
        &display_other_tab,
        &display_settings_tab
    };

    static void (*player_tab[])(void) = {
        &display_player_tab,
        &display_player_other_tab,
        &display_player_visual_tab,
        &display_player_settings_tab,
        &display_player_pvp_tab
    };

    static void (*world_tab[])(void) = {
        &display_world_tab,
        &display_world_options_tab,
        &display_world_generation_tab,
        &display_world_entities_tab,
        &display_world_liquids_tab,
        &display_world_infinite_tab,
        &display_world_enchant_tab,
        &display_world_other_tab
    };

    if (menu.menu_tab_index == 1)
        return player_tab[menu.player_tab_index]();
    if (menu.menu_tab_index == 2)
        return world_tab[menu.world_tab_index]();
    return menu_tab[menu.menu_tab_index]();
}
