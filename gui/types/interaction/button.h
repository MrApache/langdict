#pragma once
#include "visual.h"

typedef struct
{
    visual *base;
} button;

button *create_button(string text, point pos, point size, callback cb);
void free_button(button *);
