#include "../include/backend.h"
#include <assert.h>
#include <stdlib.h>

int rand_int(int a, int b)
{
    assert(a < b);
    return a + rand() % (b - a);
}

double rand_double(double min, double sup)
{
    double t;
    t = rand() / (RAND_MAX + 1.0);
    return (1 - t) * min + t * sup;
}

Vector dir_to_vec(Direction dir)
{
    Vector res = {0.0, 0.0};
    switch (dir)
    {
        case UP:    res.y = -1.0;   break;
        case DOWN:  res.y = +1.0;   break;
        case LEFT:  res.x = -1.0;   break;
        case RIGHT: res.x = +1.0;   break;
    }
    return res;
}

double lerp(double start, double end, double t)
{
    return (1 - t) * start + t * end;
}
