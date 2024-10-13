#define _POSIX_C_SOURCE 200112L
#include "../include/detect.h"
#include "../include/vector.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

/**
 * @brief Check if the point is adjacent to a wall. point is assumed to have at
 * least one integer coordinate.
 *
 * @param room_p pointer to the room
 * @param point point to check, must be inside the room
 * @return int 1 if point is adjacent to a wall, 0 otherwise
 */
static int _check_point(Room *room_p, Vector point)
{
    int b = (int)point.y;
    int a = (int)point.x;
    /* both coordinates are ints => check all cells around point */
    if (floor(point.y) == point.y && floor(point.x) == point.x)
        return room_p->cells[b - 1][a - 1] == WALL ||
               room_p->cells[b - 1][a] == WALL ||
               room_p->cells[b][a - 1] == WALL ||
               room_p->cells[b][a] == WALL;
    /* y is int => check up and down */
    if (floor(point.y) == point.y)
        return room_p->cells[b - 1][a] == WALL ||
               room_p->cells[b][a] == WALL;
    /* x is int => check left and right */
    return room_p->cells[b][a - 1] == WALL ||
           room_p->cells[b][a] == WALL;
}

/**
 * @brief Check if there's a vertical wall between the guard and the player.
 *
 * @param room_p pointer to the room
 * @param guard_p pointer to the guard
 * @param player_p pointer to the player
 * @return int 1 is there's a wall, 0 otherwise
 */
static int _check_vertical(Room *room_p, Guard *guard_p, Player *player_p)
{
    /* p0 = start of segment, p1 = end of segment */
    Vector p0, p1, current;
    double t;
    int y_start, y_end;
    if (guard_p->position.y < player_p->position.y)
    {
        p0 = guard_p->position;
        p1 = player_p->position;
    }
    else
    {
        p0 = player_p->position;
        p1 = guard_p->position;
    }
    y_start = (int)ceil(p0.y);
    y_end = (int)floor(p1.y);
    for (current.y = y_start; current.y <= y_end; current.y++)
    {
        t = (current.y - p0.y) / (p1.y - p0.y);
        current.x = lerp(p0.x, p1.x, t);
        if (_check_point(room_p, current))
            return 1;
    }
    return 0;
}

/**
 * @brief Check if there's a horizontal wall between the guard and the player.
 *
 * @param room_p pointer to the room
 * @param guard_p pointer to the guard
 * @param player_p pointer to the player
 * @return int 1 is there's a wall, 0 otherwise
 */
static int _check_horizontal(Room *room_p, Guard *guard_p, Player *player_p)
{
    /* p0 = start of segment, p1 = end of segment */
    Vector p0, p1, current;
    double t;
    int x_start, x_end;
    if (guard_p->position.x < player_p->position.x)
    {
        p0 = guard_p->position;
        p1 = player_p->position;
    }
    else
    {
        p0 = player_p->position;
        p1 = guard_p->position;
    }
    x_start = (int)ceil(p0.x);
    x_end = (int)floor(p1.x);
    for (current.x = x_start; current.x <= x_end; current.x++)
    {
        t = (current.x - p0.x) / (p1.x - p0.x);
        current.y = lerp(p0.y, p1.y, t);
        if (_check_point(room_p, current))
            return 1;
    }
    return 0;
}

/**
 * @brief Check if the guard can see the player.
 *
 * @param room_p pointer to the room
 * @param guard_p pointer to the guard
 * @param player_p pointer to the player
 * @return int 1 if the guard can see the player, 0 otherwise
 */
static int _guard_detect(Room *room_p, Guard *guard_p, Player *player_p)
{
    int blocked = 0;
    if (dist(player_p->position, guard_p->position) > GUARD_NORMAL_RANGE)
        return 0;
    if (guard_p->position.y != player_p->position.y)
        blocked = _check_vertical(room_p, guard_p, player_p);
    if (!blocked && guard_p->position.x != player_p->position.x)
        blocked = _check_horizontal(room_p, guard_p, player_p);
    return !blocked;
}

int check_detection(Room *room_p, Guard *guards, Player *player_p)
{
    int i;
    assert(room_p != NULL);
    assert(guards != NULL);
    assert(player_p != NULL);
    if (!player_p->visible)
        return 0;
    for (i = 0; i < NB_GUARDS; i++)
        if (_guard_detect(room_p, guards + i, player_p))
            return 1;
    return 0;
}