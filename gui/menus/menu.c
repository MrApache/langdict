#include <stdlib.h>
#include <stdarg.h>
#include "include/menu.h"

Stack(stack_menu, Menu *)

Option *create_option(string name, int y, int x, callback callback, bool interactable)
{
    Option *option = malloc(sizeof(Option));
    option->name = name;
    option->y = y;
    option->x = x;
    option->callback = callback;
    option->interactable = interactable;
    return option;
}

Menu *create_menu(string name, int opt_count, ...)
{
    Menu *menu = malloc(sizeof(Menu));
    menu->name = name;
    menu->options = malloc(sizeof(Option) * opt_count);
    menu->opt_count = opt_count;

    va_list factor;
    va_start(factor, opt_count);
    for(int i = 0; i < opt_count; i++)
    {
        menu->options[i] = va_arg(factor, Option *);
    }
    va_end(factor);
    return menu;
}

Menu *invoke_opt(Option *option)
{
    return (Menu *)option->callback();
}

void free_options(Option *opt)
{
    free(opt);
}

void free_menu(Menu *menu)
{
    int i;

    for (i = 0; i < menu->opt_count; ++i) {
        free_options(menu->options[i]);
    }

    free(menu->options);
    free(menu);
}
