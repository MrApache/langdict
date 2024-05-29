#pragma once
#include "point.h"
#include "interact.h"
#include "iristr.h"

typedef void (*print_func)(int attrb, string text, point pos);
typedef void (*draw_func)(print_func, const void *src);

typedef struct events
{
    callback on_select;
    callback on_deselect;
    callback on_invoke;
} events;

typedef struct draw_data
{
    draw_func func;
    void *source;

}draw_data;

typedef struct visual_base
{
    string name;
    point position;
    interact interaction;
    draw_data draw;
} visual;

#define draw_data_default() create_draw_data(NULL, NULL)
draw_data create_draw_data(draw_func, void *);
visual *create_visual(string name, point pos, interact interaction, draw_data d);
void free_visual(visual *);