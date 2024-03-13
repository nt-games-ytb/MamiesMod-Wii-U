/*
** MAMIESMOD PROJECT
** MamiesMod-Wii-U
** File description:
** The mamiesmod_client.h
*/

#pragma region Includes
#include <cstdint>
#include <cstddef>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>

#include "../miscellaneous/miscellaneous.hpp"
#include "../miscellaneous/time.hpp"
#pragma endregion Includes

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAMIESMOD_CLIENT_H_
    #define MAMIESMOD_CLIENT_H_

    #define get_variable(type, address) (*(type*)(address))
    #define swprintf ((int32_t(*)(wchar_t*, int32_t, const wchar_t*, ...))0x0382C8C0)

    #define white 0xFFFFFFFF
    #define grey 0xFF808080
    #define red_on 0xFFFF0000
    #define red_off 0xFF800000
    #define green_on 0xFF00FF00
    #define green_off 0xFF008000

    #define max_elements 10
    #define element_1_pos_y  200.0f
    #define element_2_pos_y  230.0f
    #define element_3_pos_y  260.0f
    #define element_4_pos_y  290.0f
    #define element_5_pos_y  320.0f
    #define element_6_pos_y  350.0f
    #define element_7_pos_y  380.0f
    #define element_8_pos_y  410.0f
    #define element_9_pos_y  440.0f
    #define element_10_pos_y  470.0f

typedef enum element_type_s {
    text,
    button,
    toggle,
    numeric
} element_type_t;

typedef struct cheat_s {
    wchar_t name[100];
    void (*cheat_function)(void);
    element_type_t type;
    bool enabled;
} cheat_t;

typedef struct notification_s {
    wchar_t *title;
    wchar_t *message;
    uint32_t title_color;
    uint32_t message_color;
    float duration;
    float animation_duration;
    //Timer timer;
    struct notification_s *next;
} notification_t;

typedef struct menu_s {
    bool opened;
    mc::Font* font;
    float position_x;
    float position_y;
    uint32_t color;
    uint opacity;
    uint menu_tab_index;
    uint player_tab_index;
    uint player_other_tab_index;
    uint player_visual_tab_index;
    uint player_settings_tab_index;
    uint player_pvp_tab_index;
    uint world_tab_index;
    uint world_options_tab_index;
    uint world_generation_tab_index;
    uint world_entities_tab_index;
    uint world_liquids_tab_index;
    uint world_infinite_tab_index;
    uint world_enchant_tab_index;
    uint world_other_tab_index;
    uint minigames_tab_index;
    uint nicknames_tab_index;
    uint build_tab_index;
    uint other_tab_index;
    uint settings_tab_index;
    bool tab_changed;
    notification_t *notifications;
} menu_t;

extern menu_t menu;

int mamiesmod_thread(int argc, void* argv);
void check_menu_status(void);
uint32_t get_text_color(int id, int index, uint32_t enable, uint32_t disable);
uint32_t get_multiple_text_color(int id, int index[], uint32_t enable, uint32_t disable);
void display_menu(void);
void help(void);
void in_world(void);
void not_in_world(void);
void test(void);
void add_notification(const wchar_t *title, const wchar_t *message, uint32_t title_color, uint32_t message_color, float duration, float animation_duration);
void remove_notification(void);
void update_notifications(void);
void always_display(void);
void display_coordinates(float size, float x, float y, uint precision, uint32_t color);
void default_display_coordinates(void);
void display_menu_tab(void);
void display_player_tab(void);
void display_player_other_tab(void);
void display_player_visual_tab(void);
void display_player_settings_tab(void);
void display_player_pvp_tab(void);
void display_world_tab(void);
void display_world_options_tab(void);
void display_world_generation_tab(void);
void display_world_entities_tab(void);
void display_world_liquids_tab(void);
void display_world_infinite_tab(void);
void display_world_enchant_tab(void);
void display_world_other_tab(void);
void display_minigames_tab(void);
void display_nicknames_tab(void);
void display_build_tab(void);
void display_other_tab(void);
void display_settings_tab(void);



void fly(void);

#endif /* MAMIESMOD_CLIENT_H_ */

#ifdef __cplusplus
}
#endif