#define _POSIX_C_SOURCE 200112L
#include "../include/vector.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

int equals(Vector *v, Vector *w)
{
    assert(v != NULL);
    assert(w != NULL);
    return v->y == w->y && v->x == w->x;
}

Vector add(Vector v, Vector w)
{
    Vector sum;
    sum.y = v.y + w.y;
    sum.x = v.x + w.x;
    return sum;
}

Vector sub(Vector v, Vector w)
{
    Vector diff;
    diff.y = v.y - w.y;
    diff.x = v.x - w.x;
    return diff;
}

Vector scale(Vector v, double num)
{
    Vector scaled;
    scaled.y = num * v.y;
    scaled.x = num * v.x;
    return scaled;
}

Vector rotate_cw(Vector v)
{
    Vector res;
    res.y = +v.x;
    res.x = -v.y;
    return res;
}

Vector rotate_ccw(Vector v)
{
    Vector res;
    res.y = -v.x;
    res.x = +v.y;
    return res;
}

Vector floored(Vector v)
{
    Vector res;
    res.y = floor(v.y);
    res.x = floor(v.x);
    return res;
}

double norm(Vector v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

double dist(Vector v, Vector w)
{
    return norm(sub(v, w));
}