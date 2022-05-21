/*
** EPITECH PROJECT, 2021
** corewar_graphic
** File description:
** quentin.c
*/

#include "rpg.h"

const sfTexture *draw_main_play(window_t *win)
{
    main_play_t *m = win->menus[MAIN];

    sfRenderTexture_clear(m->rtex, sfBlack);
    draw_graph(m->war);
    sfSprite *s = init_sprite_from_texture(sfRenderTexture_getTexture(m->war->rtex));

    sfRenderTexture_drawSprite(m->rtex, s, NULL);
    sfRenderTexture_display(m->rtex);
    sfSprite_destroy(s);
    return sfRenderTexture_getTexture(m->rtex);
}

void main_play_ev(window_t *win, sfEvent ev)
{
    main_play_t *m = win->menus[MAIN];

    graph_ev(m->war, ev);
}

main_play_t *create_main_play(sfVector2f size, corewar_grap_t *graph)
{
    main_play_t *m = malloc(sizeof(main_play_t));

    m->rtex = sfRenderTexture_create(size.x, size.y, 0);
    m->war = create_graphic_war((sfVector2f){size.x * 0.6, size.y}, graph);
    return m;
}