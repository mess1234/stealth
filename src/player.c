#include "../include/player.h"

Player init_player()
{
    Player player;
    player.position.y = 2.0;
    player.position.x = 2.0;
    player.direction = RIGHT;
    player.speed = 0.0;
    player.time_spent = 0.0;
    player.mana = 0;
    player.visible = true;
    player.overloaded = false;
    return player;
}

int player_win(Player player){
    if(player.position.x >= 1 && player.position.x <= 3 &&
        player.position.y >= 1 && player.position.y <= 3)
    {
        return 1;
    }
    return 0;
}