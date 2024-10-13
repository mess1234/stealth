#ifndef __COLLISION_H
#define __COLLISION_H
/**
 * @file collision.h
 * @brief This file take care of player collision with walls
 * @author CHERRATI Sid-Ali
 * @author MESSEANT ADRIEN
 * @date 12/01/2023
*/
#include "player.h"
#include "room.h"
#include "vector.h"

/**
 * @brief Check wall collisions and update *new_pos accordlingly
 *
 * @param room_p pointer to the room
 * @param player_p pointer to the player (with old position)
 * @param new_pos new player position, ignoring wall collisions
 */
void compute_collisions(Room *room_p, Player *player_p, Vector *new_pos);

#endif /* __COLLISION_H */