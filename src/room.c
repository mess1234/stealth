#include "../include/room.h"
#include "../include/backend.h"
#include <stdlib.h>
#include <stdio.h>

#define MIN_SIDE 9
#define DOOR_SIZE 3
#define NB_RELIC 3

static void _place_walls_rec(Cell **cells, int y0, int x0, int y1, int x1);
static void _cut_vertical(Cell **cells, int y0, int x0, int y1, int x1);
static void _cut_horizontal(Cell **cells, int y0, int x0, int y1, int x1);

/**
 * @brief Place walls in a room.
 *
 * @param cells Cells of the room
 * @param y0 y coordinate of the upper left corner (inclusive)
 * @param x0 x coordinate of the upper left corner (inclusive)
 * @param y1 y coordinate of the lower right corner (exclusive)
 * @param x1 x coordinate of the lower right corner (exclusive)
 */
static void _place_walls_rec(Cell **cells, int y0, int x0, int y1, int x1)
{
    int dy, dx, delta;
    dy = y1 - y0;
    dx = x1 - x0;
    delta = (dx > dy) ? dx : dy;
    if (delta < 2 * MIN_SIDE + 1)
        return;
    if (delta < 4 * MIN_SIDE && rand_int(0, 2))
        return;
    if (dx > dy)
        _cut_vertical(cells, y0, x0, y1, x1);
    else
        _cut_horizontal(cells, y0, x0, y1, x1);
}

/**
 * @brief Place a vertical wall in a room.
 *
 * @param cells Cells of the room
 * @param y0 y coordinate of the upper left corner (inclusive)
 * @param x0 x coordinate of the upper left corner (inclusive)
 * @param y1 y coordinate of the lower right corner (exclusive)
 * @param x1 x coordinate of the lower right corner (exclusive)
 */
static void _cut_vertical(Cell **cells, int y0, int x0, int y1, int x1)
{
    int wall_x, door_y, i;
    wall_x = rand_int(x0 + MIN_SIDE, x1 - MIN_SIDE);
    for (i = y0; i < y1; i++)
        cells[i][wall_x] = WALL;
    /* Leave an opening at one of the ends */
    door_y = rand_int(0, 2) ? y0 : y1 - DOOR_SIZE;
    for (i = 0; i < DOOR_SIZE; i++)
        cells[door_y + i][wall_x] = DOOR;
    /* Continue */
    _place_walls_rec(cells, y0, x0, y1, wall_x);
    _place_walls_rec(cells, y0, wall_x + 1, y1, x1);
}

/**
 * @brief Place a horizontal wall in a room.
 *
 * @param cells Cells of the room
 * @param y0 y coordinate of the upper left corner (inclusive)
 * @param x0 x coordinate of the upper left corner (inclusive)
 * @param y1 y coordinate of the lower right corner (exclusive)
 * @param x1 x coordinate of the lower right corner (exclusive)
 */
static void _cut_horizontal(Cell **cells, int y0, int x0, int y1, int x1)
{
    int wall_y, door_x, j;
    wall_y = rand_int(y0 + MIN_SIDE, y1 - MIN_SIDE);
    for (j = x0; j < x1; j++)
        cells[wall_y][j] = WALL;
    /* Leave an opening at one of the ends */
    door_x = rand_int(0, 2) ? x0 : x1 - DOOR_SIZE;
    for (j = 0; j < DOOR_SIZE; j++)
        cells[wall_y][door_x + j] = DOOR;
    /* Continue */
    _place_walls_rec(cells, y0, x0, wall_y, x1);
    _place_walls_rec(cells, wall_y + 1, x0, y1, x1);
}

Cell **create_room_cells(void)
{
    int i, j;
    Cell **cells;
    /* Allocate memory */
    cells = (Cell **)malloc(ROOM_HEIGHT * sizeof(Cell *));
    if (cells == NULL)
    {
        fprintf(stderr, "ERROR : Could not create room cells\n");
        return NULL;
    }
    for (i = 0; i < ROOM_HEIGHT; i++)
    {
        cells[i] = (Cell *)malloc(ROOM_WIDTH * sizeof(Cell));
        if (cells[i] == NULL)
        {
            fprintf(stderr, "ERROR : Could not create room cells\n");
            /* Free allocated lines */
            for (j = 0; j < i; j++)
                free(cells[i]);
            free(cells);
            return NULL;
        }
    }
    return cells;
}

void free_room_cells(Cell **cells)
{
    int i;
    for (i = 0; i < ROOM_HEIGHT; i++)
        free(cells[i]);
    free(cells);
}

void place_walls(Cell **cells)
{
    int i, j;
    /* Outer walls */
    for (i = 0; i < ROOM_HEIGHT; i++)
    {
        for (j = 0; j < ROOM_WIDTH; j++)
        {
            if (i == 0 || i == ROOM_HEIGHT - 1 ||
                j == 0 || j == ROOM_WIDTH - 1)
                cells[i][j] = WALL;
            else
                cells[i][j] = MANA_ON;
        }
    }
    /* Inner Walls */
    _place_walls_rec(cells, 1, 1, ROOM_HEIGHT - 1, ROOM_WIDTH - 1);
}

void place_relics(Room *room_p, Vector player_start)
{
    Vector tmp;
    room_p->remaining_relics = 0;
    while (room_p->remaining_relics < NB_RELIC)
    {
        tmp.y = rand_int(0, ROOM_HEIGHT);
        tmp.x = rand_int(0, ROOM_WIDTH);
        switch (room_p->cells[(int)tmp.y][(int)tmp.x])
        {
            case MANA_OFF:  break;
            case MANA_ON:   break;
            default:        continue; /* can't place relic on wall or door */
        }
        if (dist(tmp, player_start) < 20)
            continue;
        room_p->cells[(int)tmp.y][(int)tmp.x] = RELIC_ON;
        room_p->remaining_relics++;
    }
}

void clean_doors(Cell **cells)
{
    int i, j;
    for (i = 0; i < ROOM_HEIGHT; i++)
        for (j = 0; j < ROOM_WIDTH; j++)
            if (cells[i][j] == DOOR)
                cells[i][j] = MANA_ON;
}
