/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** transition.c
*/

#include "rpg.h"

void destroy_create_play(play_t *p);

static void switch_color_dir(window_t *win, int *dir)
{
    win->state = win->next_state;
    *dir = -1;
    if (win->state == EXIT)
        sfRenderWindow_close(win->win);
    if (win->state == HOME) {
        destroy_create_play(win->menus[PLAY]);
        win->menus[PLAY] = create_play(win_size(win));
    }
}

static void reset_lum(window_t *win, int *dir, sfColor *lum)
{
    *dir = 1;
    win->is_transition = false;
    *lum = (sfColor){255, 255, 255, 255};
}

static void update_lum(sfColor *lum, int *fac)
{
    lum->a -= *fac;
    lum->b -= *fac;
    lum->r -= *fac;
    lum->g -= *fac;
}

void update_transition(window_t *win, sfSprite *s)
{
    static int dir = 1;
    int fac = dir * 24;
    static sfColor lum = {255, 255, 255, 255};

    if (win->is_transition && get_elapsed_time(win->lum_clock) > 33333) {
        if (lum.a == 39)
            switch_color_dir(win, &dir);
        update_lum(&lum, &fac);
        sfSprite_setColor(s, lum);
        if (dir == -1 && lum.a == 255)
            reset_lum(win, &dir, &lum);
        restart_clock(win->lum_clock);
    }
    sfSprite_setColor(s, lum);
}
