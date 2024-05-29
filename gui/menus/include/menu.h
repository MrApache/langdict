#pragma once
#include <stddef.h>
#include <stdbool.h>
#include "collections/stack.h"
#include "iristr.h"

typedef void *(*callback)();

typedef struct Option
{
    int x;
    int y;
    string name;
    callback callback;
    bool interactable;
} Option;

typedef struct Menu
{
    string name;
    Option **options;
    int opt_count;
} Menu;

STACK_HEADER(stack_menu, Menu *)
Option *create_option(string name, int y, int x, callback callback, bool interactable);
Menu *create_menu(string name, int opt_count, ...);
Menu *invoke_opt(Option *option);
void free_menu(Menu *menu);
void free_options(Option *opt);

#define opt_center(NAME, Y, X, CALLBACK, INTERACTABLE) \
    create_option(NAME, Y, X - (int)strlen(NAME) / 2, (callback) CALLBACK, INTERACTABLE)
