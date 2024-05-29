#pragma once

typedef struct point
{
    int y;
    int x;
} point;

point create_point(int y, int x);

#define point_zero() create_point(0, 0)
#define point_one() create_point(1, 1)
#define point(y, x) create_point(y, x)