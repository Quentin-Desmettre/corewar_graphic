/*
** EPITECH PROJECT, 2021
** corewar_graphic
** File description:
** noa.c
*/

#include "rpg.h"
#include "op.h"

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

void camera_move_mouse(graphic_war_t *g)
{
    sfRenderWindow *windows = window(NULL)->win;
    sfVector2i mpos = sfMouse_getPositionRenderWindow(windows);
    sfVector2f pos;

    if (!g->oldMousePos.x && !g->oldMousePos.y)
        g->oldMousePos = sfMouse_getPositionRenderWindow(windows);
    pos = (sfVector2f) {(float)g->oldMousePos.x -
    (float)mpos.x, (float)g->oldMousePos.y - (float)mpos.y};
    sfView_move(g->view,
    (sfVector2f){pos.x * 2.2, pos.y * 2.2});
    g->oldMousePos =
    sfMouse_getPositionRenderWindow(windows);
}

void ingame_zoom(graphic_war_t *g, sfEvent ev)
{
    static int zoom_ratio = 0;

    if (ev.type != sfEvtMouseWheelScrolled) {
        sfRenderTexture_setView(g->rtex, g->view);
        return;
    }
    if (ev.mouseWheelScroll.delta < 0.0 && zoom_ratio < 2) {
        zoom_ratio += 1;
        sfView_zoom(g->view, (float)(1.0 / 1.1));
    } else if (ev.mouseWheelScroll.delta > 0.0 && zoom_ratio > -8) {
        zoom_ratio -= 1;
        sfView_zoom(g->view, (float)1.1);
    }
    sfRenderTexture_setView(g->rtex, g->view);
}

void graph_ev(graphic_war_t *g, sfEvent ev)
{
    camera_move_mouse(g);
    ingame_zoom(g, ev);
}

graphic_war_t *create_graphic_war(sfVector2f size, corewar_grap_t *graph)
{
    graphic_war_t *g = malloc(sizeof(graphic_war_t));

    g->rtex = sfRenderTexture_create(size.x, size.y, 0);
    g->view = sfView_copy(sfRenderTexture_getView(g->rtex));
    graph->current_cycle = 0;
    g->graph = graph;
    g->byte = init_text("", (size.x / 64) / 1.5);
    g->rect = create_rectangle((sfVector2f){size.x / 64, size.x / 64}, sfRed, 0, sfBlack);
    sfRectangleShape_setPosition(g->rect, (sfVector2f){0, 0});
    sfText_setColor(g->byte, sfWhite);
    g->oldMousePos = (sfVector2i){0, 0};
    return (g);
}
