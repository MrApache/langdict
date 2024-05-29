#pragma once
#include <stddef.h>
#include <stdbool.h>
#include "collections/stack.h"
#include "iristr.h"
#include "visual.h"

typedef struct Menu
{
    visual *base;
    string name;
    int opt_count;
    visual **options;
} Menu;

STACK_HEADER(stack_menu, Menu *)
Menu *create_menu(string name, int opt_count, ...);
void free_menu(Menu *menu);

//#define opt_center(NAME, Y, X, CALLBACK, INTERACTABLE) \
//    create_option(NAME, Y, X - (int)strlen(NAME) / 2, (callback) CALLBACK, INTERACTABLE)
