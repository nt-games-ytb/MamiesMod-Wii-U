/*
** EPITECH PROJECT, 2024
** MamiesMod-Wii-U
** File description:
** The notification.cpp
*/

#include "mamiesmod_client.hpp"

void add_notification(const wchar_t *title, const wchar_t *message, uint32_t title_color, uint32_t message_color, float duration, float animation_duration)
{
    notification_t *new_notification = (notification_t *)malloc(sizeof(notification_t));
    notification_t *tmp = menu.notifications;

    new_notification->title = wcsdup(title);
    new_notification->message = wcsdup(message);
    new_notification->title_color = title_color;
    new_notification->message_color = message_color;
    new_notification->duration = duration;
    new_notification->animation_duration = animation_duration;
    //new_notification->timer = Timer();
    new_notification->next = NULL;

    if (menu.notifications == NULL) {
        menu.notifications = new_notification;
        return;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_notification;
}

void remove_notification(void)
{
    notification_t *tmp = menu.notifications;
    notification_t *next = tmp->next;

    free(tmp->title);
    free(tmp->message);
    free(tmp);
    menu.notifications = next;
}

void update_notifications(void)
{
    static float time = 0.0f;

    if (menu.notifications == NULL)
        return;
    if (time / 60.0f >= menu.notifications->duration + (menu.notifications->animation_duration * 2)) {
        remove_notification();
        time = 0;
    } else {
        misc::GUI::DisplayText(menu.font, menu.notifications->title, 2.0f, WIDTH / 2, HEIGHT / 2, menu.notifications->title_color, true);
        time++;
    }
}