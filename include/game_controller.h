#ifndef __GAME_CONTROLLER_H
#define __GAME_CONTROLLER_H
/**
 * @file game_controller.h
 * @brief File taking care of game controle
 * @author CHERRATI Sid-Ali
 * @author MESSEANT ADRIEN
 * @date 12/01/2023
*/
#include "room.h"
#include "player.h"
#include "guard.h"
#include "frontend.h"
#include <stdbool.h>

/**
 * @brief Initialise the game.
 * 
 * @param room_p Pointer to board rooms informations
 * @param player_p Pointer to player informations
 * @param guards_p 2D array of guards
 * @return int 1 if issues creating cells\n
 * and 2 if issues creating guards, 0 is returned if no errors occured.
 */

int init_game(Room *room_p, Player *player_p, Guard **guards_p);
/**
 * @brief Determine player action
 * 
 * @param room_p Pointer to room
 * @param pl Pointer to player informations
 * @param input_p pointer to player input
 * @param quit Pointer to quit option (if player decides to quit)
 */
void player_action(Room *room_p, Player *pl, InputData *input_p, bool *quit);

/**
 * @brief Moving guards inside room
 * 
 * @param room_p Pointer to room
 * @param guards pointer to guard
 */
void move_guards(Room *room_p, Guard *guards);

#endif /* __GAME_CONTROLLER_H */