#include "../include/guard.h"
#include <stdio.h>
#include <stdlib.h>

/* we need to free the allocation at the end of game */
Guard *create_guards(void)
{
    Guard *guards;
    if ((guards = malloc(NB_GUARDS * sizeof(Guard))) == NULL)
    {
        fprintf(stderr, "ERROR : Could not create guards\n");
        return NULL;
    }
    return guards;
}

void init_guards(Room *room_p, Guard *guards, Vector player_start)
{
    Vector pos;
    int count = 0;
    while (count < NB_GUARDS)
    {
        pos.y = rand_double(0, ROOM_HEIGHT);
        pos.x = rand_double(0, ROOM_WIDTH);
        switch (room_p->cells[(int)pos.y][(int)pos.x]) /* (int) truncates positive double */
        {
            case MANA_OFF:
            case MANA_ON:
                break;
            default:
                continue; /* can't place guard on wall or door */
        }
        if (dist(pos, player_start) < 20)
            continue;
        /* place guard there */
        guards[count].position = pos;
        guards[count].direction = rand_int(0, 4);
        guards[count].speed = rand_double(GUARD_NORMAL_MIN_VELOCITY,
                                          GUARD_NORMAL_MAX_VELOCITY);
        count++;
    }
}