/*
** EPITECH PROJECT, 2024
** MamiesMod-Wii-U
** File description:
** The not_in_game.c
*/

#include "mamiesmod_client.hpp"

menu_t menu;

void init_menu(void)
{
    menu.opened = false;
    menu.font = mc::Minecraft::getInstance()->defaultFonts;
    menu.position_x = 1120;
    menu.position_y = 340;
    menu.color = 0xFF202020;
    menu.opacity = 100;
    menu.menu_tab_index = 0;
    menu.player_tab_index = 0;
    menu.player_other_tab_index = 0;
    menu.player_visual_tab_index = 0;
    menu.player_settings_tab_index = 0;
    menu.player_pvp_tab_index = 0;
    menu.world_tab_index = 0;
    menu.world_options_tab_index = 0;
    menu.world_generation_tab_index = 0;
    menu.world_entities_tab_index = 0;
    menu.world_liquids_tab_index = 0;
    menu.world_infinite_tab_index = 0;
    menu.world_enchant_tab_index = 0;
    menu.world_other_tab_index = 0;
    menu.minigames_tab_index = 0;
    menu.nicknames_tab_index = 0;
    menu.build_tab_index = 0;
    menu.other_tab_index = 0;
    menu.settings_tab_index = 0;
    menu.tab_changed = false;
    menu.notifications = NULL;
}

void not_in_world(void)
{
    static int start = 0;

    if (!start) {
        init_menu();
        start = 1;
    }
    misc::GUI::DisplayText(menu.font, L"MamiesModClient not in world", 2.0f, 1.0f, 1.0f, 0xFFFFFFFF, true);
    check_menu_status();
    always_display();
    help();
}
