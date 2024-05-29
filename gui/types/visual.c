#include <malloc.h>
#include "visual.h"

draw_data create_draw_data(draw_func df, void *src)
{
    draw_data d = {df, src};
    return d;
}

visual *create_visual(string name, point pos, interact interaction, draw_data d)
{
    visual *v = malloc(sizeof(visual));
    v->name = name;
    v->position = pos;
    v->interaction = interaction;
    v->draw = d;
    return v;
}

void free_visual(visual *v)
{
    free(v);
}
