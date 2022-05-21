/*
** EPITECH PROJECT, 2021
** corewar_graphic
** File description:
** noa.c
*/

#include "rpg.h"
#include "op.h"

// typedef struct {
//     sfRenderTexture *rtex;
//     corewar_grap_t *graph;
//     sfView *view;
//     sfText *byte;
//     sfRectangleShape *rect;
// } graphic_war_t;

void draw_graph(graphic_war_t *g)
{
    sfRenderTexture_clear(g->rtex, sfBlack);
    sfVector2u size = sfRenderTexture_getSize(g->rtex);
    sfVector2f pos = {0, 0};
    // rtex clear
    for (int i = 0; i < 64; i++) {
        sfRenderTexture_drawRectangleShape(g->rtex, g->rect, 0);
        pos.x += size.x / 64.0;
        sfRectangleShape_setPosition(g->rect, pos);
    }

    // rtex draw des couleur puis la méoire

    sfRenderTexture_display(g->rtex);
    // rtex display
}

void graph_ev(graphic_war_t *g, sfEvent ev)
{
    // move cam with mouse

    // zoom in/out with scroll
}

graphic_war_t *create_graphic_war(sfVector2f size, corewar_grap_t *graph)
{
    // size: size of the render texture
    graphic_war_t *g = malloc(sizeof(graphic_war_t));

    g->rtex = sfRenderTexture_create(size.x, size.y, 0);
    g->view = sfView_copy(sfRenderTexture_getView(g->rtex));
    g->graph = graph;
    g->rect = create_rectangle((sfVector2f){size.x / 64, size.x / 64}, sfWhite, 0, sfBlack);
    sfRectangleShape_setPosition(g->rect, (sfVector2f){0, 0});
    return (g);
}
