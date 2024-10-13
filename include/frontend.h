#ifndef __FRONTEND_H
#define __FRONTEND_H
/**
 * @file frontend.h
 * @brief This file take care of all graphic design of the game.
 * @author CHERRATI Sid-Ali
 * @author MESSEANT ADRIEN
 * @date 12/01/2023
*/
#include "room.h"
#include "player.h"
#include "guard.h"
#include <MLV/MLV_all.h>

#define CELL_SIDE       20 /* sidelength of a cell in pixels */
#define WINDOW_HEIGHT   (CELL_SIDE * ROOM_HEIGHT)
#define WINDOW_WIDTH    (CELL_SIDE * ROOM_WIDTH)
#define FRAMERATE       60

typedef struct _InputData
{
    MLV_Event event;
    MLV_Keyboard_button key;
    MLV_Button_state state;
} InputData;

/**
 * @brief Get user input data and write it to input_p.
 *
 * @param input_p address where input will be stored
 */
void get_user_input(InputData *input_p);

/**
 * @brief Draw one frame.
 * 
 * @param room_p pointer to the room
 * @param player_p pointer to the player
 * @param guards array containing the guards
 */
void draw_frame(Room *room_p, Player *player_p, Guard *guards);

/**
 * @brief Draw first loading game menu
 * @param void
 */
void _draw_start_menu(void);

/**
 * @brief Draw first loading game menu
 * @param quit Boolean values to determine if player wished to quit the game
 * @param restart Boolean values to determine if player wished to restart the game\n
 * (play again)
 * @param rgstr register situation on or off
 */
void _draw_end_win(bool *quit, bool *restart, int state, bool *rgstr);

/**
 * @brief Draw quit and restart buttons
 * @return Function returns 1 if restart button pressed, 2 if quit button pressed\n
 * and 0 if neither of them is pressed
 */
int draw_quit_restart();

#endif /* __FRONTEND_H */