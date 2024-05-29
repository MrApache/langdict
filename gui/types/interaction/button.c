#include <malloc.h>
#include "global.h"
#include "button.h"

static void draw_button(print_func print, const void *src)
{
    button *btn = (button *)src;
    print(A_NORMAL, btn->base->name, btn->base->position);
}

button *create_button(string text, point pos, point size, callback cb)
{
    button *btn = malloc(sizeof(button));
    interact in = create_interaction(true, pos, size, cb);
    visual *base = create_visual(text, pos, in, create_draw_data(draw_button, btn));
    btn->base = base;
    return btn;
}

void free_button(button *b)
{
    free_visual(b->base);
    free(b);
}
