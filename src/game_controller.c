#define _POSIX_C_SOURCE 200112L
#include "../include/backend.h"
#include "../include/collision.h"
#include "../include/game_controller.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

static void _take_relic(Player *player_p, Room *room_p)
{
    MLV_Sound *relic_sound;
    int p_y, p_x;

    p_y = (int)player_p->position.y;
    p_x = (int)player_p->position.x;

    if (room_p->cells[p_y][p_x] == RELIC_ON)
    {
        /*turning off relic*/
        room_p->cells[p_y][p_x] = RELIC_OFF;
        room_p->remaining_relics--;

        /*playing sound*/
        if (MLV_init_audio())
        {
            fprintf(stderr,
                    "L'infrastructure audio de la librairie MLV ne s'est pas \
                    correctement initialisée.");
            exit(EXIT_FAILURE);
        }
        relic_sound = MLV_load_sound("lib/collect_sound.ogg");
        MLV_play_sound(relic_sound, 1.0);
    }
}

/**
 * @brief Move the player in the given direction.
 * 
 * @param player_p pointer to the player
 * @param room_p pointer to the room
 * @param dir movement direction
 */
static void _move_player(Player *player_p, Room *room_p, Direction dir)
{
    Vector dir_vec, new_pos;
    /* Adjust speed */
    if (dir == player_p->direction)
        player_p->speed = fmin(player_p->speed + PLAYER_ACCEL,
                               PLAYER_NORMAL_MAX_SPEED);
    else
    {
        player_p->direction = dir;
        player_p->speed = PLAYER_START_SPEED;
    }
    /* Compute new position */
    dir_vec = dir_to_vec(player_p->direction);
    new_pos = add(player_p->position, scale(dir_vec, player_p->speed * V));
    compute_collisions(room_p, player_p, &new_pos);
    /* Move */
    player_p->position = new_pos;
}

/**
 * @brief Move one guard.
 * 
 * @param guard_p pointer to the guard
 * @param room_p pointer to the room
 */
static void _move_guard(Guard *guard_p, Room *room_p)
{
    Vector pos_diff;
    int p_y, p_x;
    pos_diff = scale(dir_to_vec(guard_p->direction), guard_p->speed * V);
    guard_p->position = add(guard_p->position, pos_diff);
    p_y = (int)guard_p->position.y;
    p_x = (int)guard_p->position.x;
    /* need a better collision test */
    if (room_p->cells[p_y][p_x] == WALL)
        guard_p->direction = (guard_p->direction + 2) % 4;
}

int init_game(Room *room_p, Player *player_p, Guard **guards_p)
{
    assert(room_p != NULL);
    assert(player_p != NULL);
    assert(guards_p != NULL);
    *player_p = init_player();
    if ((room_p->cells = create_room_cells()) == NULL)
        return 1;
    if ((*guards_p = create_guards()) == NULL)
    {
        free_room_cells(room_p->cells);
        return 2;
    }
    place_walls(room_p->cells);
    place_relics(room_p, player_p->position);
    init_guards(room_p, *guards_p, player_p->position);
    clean_doors(room_p->cells);
    return 0;
}

void player_action(Room *room_p, Player *pl, InputData *input_p, bool *quit)
{
    int cell_y, cell_x;
    /* Movement and abilities */
    if (input_p->state == MLV_RELEASED)
    {
        pl->speed = PLAYER_START_SPEED;
        return;
    }
    switch (input_p->key)
    {
        /*case MLV_KEYBOARD_ESCAPE:   *quit = true;   break;*/
        case MLV_KEYBOARD_z:
        case MLV_KEYBOARD_UP:       _move_player(pl, room_p, UP);       break;
        case MLV_KEYBOARD_s:
        case MLV_KEYBOARD_DOWN:     _move_player(pl, room_p, DOWN);     break;
        case MLV_KEYBOARD_q:
        case MLV_KEYBOARD_LEFT:     _move_player(pl, room_p, LEFT);     break;
        case MLV_KEYBOARD_d:
        case MLV_KEYBOARD_RIGHT:    _move_player(pl, room_p, RIGHT);    break;
        case MLV_KEYBOARD_LSHIFT:
        case MLV_KEYBOARD_RSHIFT:   pl->overloaded = true;  break;
        case MLV_KEYBOARD_SPACE:    pl->visible = false;    break;
        default:                    break;
    }
    /* Get mana */
    cell_y = (int)pl->position.y;
    cell_x = (int)pl->position.x;
    if (room_p->cells[cell_y][cell_x] == MANA_ON)
    {
        room_p->cells[cell_y][cell_x] = MANA_OFF;
        pl->mana++;
    }
    /* Use mana */
    if (pl->overloaded)
    {
        pl->speed = PLAYER_SWIFT_MAX_SPEED;
        pl->mana -= 2;
    }
    if (!pl->visible)
        pl->mana--;
    if (pl->mana <= 0)
    {
        pl->visible = true;
        pl->overloaded = false;
        pl->speed = fmin(pl->speed, PLAYER_NORMAL_MAX_SPEED);
        pl->mana = 0;
    }
    /* Relic */
    _take_relic(pl, room_p);
}

void move_guards(Room *room_p, Guard *guards)
{
    int i;
    for (i = 0; i < NB_GUARDS; i++)
        _move_guard(guards + i, room_p);
}