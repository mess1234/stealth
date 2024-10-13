#define _POSIX_C_SOURCE 199309L
#include "../include/detect.h"
#include "../include/frontend.h"
#include "../include/game_controller.h"
#include "../include/guard.h"
#include "../include/player.h"
#include "../include/room.h"
#include "../include/score.h"
#include <MLV/MLV_all.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *const argv[])
{
    InputData input;
    struct timespec start_time, end_time;
    double frame_time, wait_time; /* in milliseconds */
    Room room;
    Guard *guards;
    Player player;
    bool quit = false, play = true, rgstr = false;
    int win = 1, loss = 0;

    /* Setup */
    srand(time(NULL)); /* for RNG */
    while(play){
        quit = false;
        if (init_game(&room, &player, &guards))
            return 1;
        MLV_create_window("Game", "Game", WINDOW_WIDTH, WINDOW_HEIGHT);
        _draw_start_menu();
        /* Draw frames */
        draw_frame(&room, &player, guards); /* first frame */
        while (!quit)
        {
            clock_gettime(CLOCK_REALTIME, &start_time);
            /* draw new frame */
            get_user_input(&input);
            player_action(&room, &player, &input, &quit);
            move_guards(&room, guards);
            draw_frame(&room, &player, guards);

            if (check_detection(&room, guards, &player))
            {
                _draw_end_win(&quit, &play, loss, &rgstr);
            }
            if(room.remaining_relics == 0 && player_win(player)){
                /*enregistrement des données*/
                _draw_end_win(&quit, &play, win, &rgstr);
                if(rgstr){
                    record_data(player.mana, player.time_spent);
                }
                _draw_end_win(&quit, &play, win, &rgstr);
            }
            /* stabilize framerate */
            clock_gettime(CLOCK_REALTIME, &end_time);
            frame_time = (end_time.tv_sec - start_time.tv_sec) * 1.0E3 +
                        (end_time.tv_nsec - start_time.tv_nsec) * 1.0E-6;
            wait_time = 1.0E3 / FRAMERATE - frame_time;
            if (wait_time > 0)
                MLV_wait_milliseconds(wait_time);
        }
        free_room_cells(room.cells);
        free(guards);
        MLV_free_window();
    }  
    return 0;
}