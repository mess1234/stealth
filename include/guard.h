#ifndef __GUARD_H
#define __GUARD_H
/**
 * @file guard.h
 * @brief Guarde module.
 * @author CHERRATI Sid-Ali
 * @author MESSEANT ADRIEN
 * @date 12/01/2023
*/
#include "room.h"
#include "backend.h"
#include "vector.h"

#define NB_GUARDS 5
#define GUARD_CHANGE 50 /* probability = 1 / GUARD_CHANGE */
#define GUARD_NORMAL_MIN_VELOCITY 0.3
#define GUARD_NORMAL_MAX_VELOCITY 0.8
#define GUARD_NORMAL_RANGE 4
#define GUARD_PANIC_VELOCITY 1.0
#define GUARD_PANIC_RANGE 6
#define GUARD_PANIC_DURATION 30

typedef struct _Guard
{
    Vector position;
    Direction direction;
    double speed;
    /*Vector velocity;*/
} Guard;

/**
 * @brief Create a guards object.
 * 
 * @return Guard* Pointer to guard
 */
Guard *create_guards(void);

/**
 * @brief Initialisation of guard
 * 
 * @param room_p Pointer to room.
 * @param guards Pointer to guard
 * @param player_start Vector of player starting coordinates
 */
void init_guards(Room *room_p, Guard *guards, Vector player_start);

#endif /* __GUARD_H */
