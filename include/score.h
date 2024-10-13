#ifndef __SCORE_H
#define __SCORE_H
#include <MLV/MLV_all.h>
/**
 * @file score.h
 * @brief Score module.
 * @author CHERRATI Sid-Ali
 * @author MESSEANT ADRIEN
 * @date 12/01/2023
*/
typedef struct {
    char name[100];
    int mana;
    double time_spent;
} Game_score;

/**
 * @brief Storing player data at the end of game if he wins
 * 
 * @param player_mana Player collected mana.
 * @param time_spent Player time spent playing the game.
 */
void record_data(int player_mana, double time_spent);

#endif /* __SCORE_H */