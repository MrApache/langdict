#pragma once
#include <stdbool.h>
#include "point.h"

typedef void (*callback)(void);

typedef struct interact
{
    bool interactable;
    point position;
    point size;
    callback callback;
}interact;

interact create_interaction(bool interactable, point pos, point size, callback callback);

#define interact_false() create_interaction(false, point_zero(), point_zero(), NULL)
#define interact_true(CALLBACK) create_interaction(true, point_zero(), point_zero(), CALLBACK)
