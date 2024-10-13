#ifndef __PLAYER_H
#define __PLAYER_H
/**
 * @file player.h
 * @brief Player module.
 * @author CHERRATI Sid-Ali
 * @author MESSEANT ADRIEN
 * @date 12/01/2023
*/
#include "backend.h"
#include "vector.h"
#include <stdbool.h>

#define PLAYER_START_SPEED 0.1
#define PLAYER_NORMAL_MAX_SPEED 0.9
#define PLAYER_SWIFT_MAX_SPEED 1.2
#define PLAYER_ACCEL 0.03

typedef struct _Player
{
    Vector position;
    Direction direction;
    double speed;
    double time_spent;
    int mana;
    bool visible;
    bool overloaded;
} Player;
/**
 * @brief Initialisation of player.
 * 
 * @return Player 
 */
Player init_player();
/**
 * @brief Detection if player back to start room
 * 
 * @param player 
 * @return int returns 1 if player is back to init position and 0 if not.
 */
int player_win(Player player);

#endif /* __PLAYER_H */