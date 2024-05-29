#pragma once
#include "visual.h"

typedef struct text_box
{
    visual *base;
} text_box;

text_box *create_text_box(string label, point pos, point intSize, callback cb);
void free_text_box(text_box *);
