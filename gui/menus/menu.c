#include <stdlib.h>
#include <stdarg.h>
#include "include/menu.h"

Stack(stack_menu, Menu *)

Menu *create_menu(string name, int opt_count, ...)
{
    visual *base = create_visual("menu-base", point_zero(), interact_false(), draw_data_default());
    Menu *menu = malloc(sizeof(Menu));
    menu->base = base;
    menu->name = name;
    menu->opt_count = opt_count;
    menu->options = malloc(sizeof(visual) * opt_count);

    va_list factor;
    va_start(factor, opt_count);
    for(int i = 0; i < opt_count; i++)
    {
        menu->options[i] = va_arg(factor, visual *);
    }
    va_end(factor);
    return menu;
}

void free_menu(Menu *menu)
{
    int i;

    for (i = 0; i < menu->opt_count; ++i) {
        free_visual(menu->options[i]);
    }

    free(menu->options);
    free(menu);
}