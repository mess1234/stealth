#define _POSIX_C_SOURCE 200112L
#include "../include/collision.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

/**
 * @brief Compute collision with the wall in front of the player and update
 * *new_pos accordingly.
 *
 * @param new_pos new player position, ignoring wall collisions
 * @param og_cell coordinates of the cell below the player (integer coords)
 * @param dir unit vector corresponding to the player's direction
 */
static void _compute_colli_adj(Vector *new_pos, Vector og_cell, Vector dir)
{
    switch ((int)dir.y)
    {
        case +1:    new_pos->y = fmin(new_pos->y, og_cell.y + 0.5); break;
        case -1:    new_pos->y = fmax(new_pos->y, og_cell.y + 0.5); break;
        default:    /* impossible */                                break;
    }
    switch ((int)dir.x)
    {
        case +1:    new_pos->x = fmin(new_pos->x, og_cell.x + 0.5); break;
        case -1:    new_pos->x = fmax(new_pos->x, og_cell.x + 0.5); break;
        default:    /* impossible */                                break;
    }
}

/**
 * @brief Check if there's a wall in front of the player and update *new_pos if
 * necessary.
 *
 * @param room_p pointer to the room
 * @param player_p pointer to the player (with old position)
 * @param new_pos new player position, ignoring wall collisions
 * @return int 1 if new_pos has been updated (meaning there's a wall in front
 * of player), 0 otherwise
 */
static int _check_adj(Room *room_p, Player *player_p, Vector *new_pos)
{
    Vector og_cell = floored(player_p->position);
    Vector dir_vec = dir_to_vec(player_p->direction);
    Vector adj_cell = add(og_cell, dir_vec);
    if (room_p->cells[(int)adj_cell.y][(int)adj_cell.x] != WALL)
        return 0;
    _compute_colli_adj(new_pos, og_cell, dir_vec);
    return 1;
}

/**
 * @brief Check if corner is the the way of the player.
 *
 * @param player_p pointer to the player (with old position)
 * @param corner corner to check, must be a corner of the cell below the player
 * @return int 1 corner is the the way of the player, 0 otherwise
 */
static int _corner_in_the_way(Player *player_p, Vector corner)
{
    Vector diff = sub(player_p->position, corner);
    int in_range;
    switch (player_p->direction)
    {
        case UP:
        case DOWN:  in_range = (-0.5 < diff.x && diff.x < 0.5); break;
        case LEFT:
        case RIGHT: in_range = (-0.5 < diff.y && diff.y < 0.5); break;
    }
    return in_range;
}

/**
 * @brief Compute collision between the player and corner and update *new_pos
 * accordingly.
 *
 * @param player_p pointer to the player (with old position)
 * @param new_pos new player position, ignoring the collisions with corner
 * @param corner corner to check, must be a corner of the cell below the player
 */
static void _compute_colli_side(Player *player_p, Vector *new_pos, Vector corner)
{
    Vector dir_vec = dir_to_vec(player_p->direction);
    Vector lim;
    double tmp;
    tmp = (corner.x - player_p->position.x);
    tmp = sqrt(0.25 - tmp * tmp); /* == |corner.y - limit| */
    lim = sub(corner, scale(dir_vec, tmp));
    switch ((int)dir_vec.y)
    {
        case +1:    new_pos->y = fmin(new_pos->y, lim.y);   break;
        case -1:    new_pos->y = fmax(new_pos->y, lim.y);   break;
        default:    break;
    }
    switch ((int)dir_vec.x)
    {
        case +1:    new_pos->x = fmin(new_pos->x, lim.x);   break;
        case -1:    new_pos->x = fmax(new_pos->x, lim.x);   break;
        default:    break;
    }
}

/**
 * @brief Check if player could collide with a wall on its side and update
 * *new_pos accordingly.
 *
 * @param room_p pointer to the room
 * @param player_p pointer to the player (with old position)
 * @param new_pos new player position, ignoring a potential collision with
 * `side`
 * @param side coordinates of the wall to check
 */
static void _check_side(Room *room_p, Player *player_p, Vector *new_pos, Vector side)
{
    Vector og_cell = floored(player_p->position);
    Vector corner;
    /* Is there even a wall ? */
    if (room_p->cells[(int)side.y][(int)side.x] != WALL)
        return;
    /* Compute corner of `side` and check if it's in the way */
    corner.y = fmax(side.y, og_cell.y);
    corner.x = fmax(side.x, og_cell.x);
    if (!_corner_in_the_way(player_p, corner))
        return;
    /* Compute new_pos */
    _compute_colli_side(player_p, new_pos, corner);
}

void compute_collisions(Room *room_p, Player *player_p, Vector *new_pos)
{
    Vector og_cell = floored(player_p->position);
    Vector dir_vec = dir_to_vec(player_p->direction);
    Vector side_cell;
    assert(player_p != NULL);
    assert(room_p != NULL);
    /* Check adjacent wall */
    if (_check_adj(room_p, player_p, new_pos))
        return;
    /* Check side walls */
    side_cell = add(og_cell, add(dir_vec, rotate_cw(dir_vec)));
    _check_side(room_p, player_p, new_pos, side_cell);
    side_cell = add(og_cell, add(dir_vec, rotate_ccw(dir_vec)));
    _check_side(room_p, player_p, new_pos, side_cell);
}