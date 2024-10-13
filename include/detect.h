#ifndef __DETECT_H
#define __DETECT_H
/**
 * @file detect.h
 * @brief This file take care of guards detection of player.
 * @author CHERRATI Sid-Ali
 * @author MESSEANT ADRIEN
 * @date 12/01/2023
*/
#include "guard.h"
#include "player.h"
#include "room.h"

/**
 * @brief Check if one of the guards can see the player.
 *
 * @param room_p pointer to the room
 * @param guards array containing the guards
 * @param player_p pointer to the player
 * @return int 1 if one guard can see the player, 0 otherwise
 */
int check_detection(Room *room_p, Guard *guards, Player *player_p);

#endif /* __DETECT_H */