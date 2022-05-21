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

void set_square_color(graphic_war_t *g, int index)
{
    sfColor colors[5] = {sfBlack, sfBlue, sfRed, sfGreen, sfMagenta};
    int color = g->graph->color[g->graph->current_cycle][index];

    sfRectangleShape_setFillColor(g->rect, colors[color]);
}

void set_letter(graphic_war_t *g, int index)
{
    unsigned char letters = g->graph->bytes[g->graph->current_cycle][index];
    char *str = unsigned_to_str_base(letters, "0123456789ABCDEF");

    sfText_setString(g->byte, str);
    free(str);
}

void draw_graph(graphic_war_t *g)
{
    int index = 0;
    sfRenderTexture_clear(g->rtex, sfBlack);
    sfVector2u size = sfRenderTexture_getSize(g->rtex);
    float offset = size.y - (size.x / 64.0 * 96);
    sfVector2f pos = {0, offset / 2};

    for (int j = 0; j < 96; j++) {
        for (int i = 0; i < 64; i++) {
            set_square_color(g, index);
            set_letter(g, index);
            sfText_setPosition(g->byte, pos);
            sfRectangleShape_setPosition(g->rect, pos);
            sfRenderTexture_drawRectangleShape(g->rtex, g->rect, 0);
            sfRenderTexture_drawText(g->rtex, g->byte, 0);
            pos.x += size.x / 64.0;
            index++;
        }
        pos.x = 0;
        pos.y += size.x / 64.0;
    }
    sfRenderTexture_display(g->rtex);
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
    graph->current_cycle = 0;
    g->graph = graph;
    g->byte = init_text("", (size.x / 64) / 1.5);
    g->rect = create_rectangle((sfVector2f){size.x / 64, size.x / 64}, sfRed, 0, sfBlack);
    sfRectangleShape_setPosition(g->rect, (sfVector2f){0, 0});
    sfText_setColor(g->byte, sfWhite);
    return (g);
}
