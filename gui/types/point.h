#pragma once

typedef struct point
{
    int y;
    int x;
} point;

point create_point(int y, int x);

#define point() create_point(0, 0);