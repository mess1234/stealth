#include "../include/frontend.h"
#include <assert.h>
#include <stdlib.h>

/**
 * @brief Draw the room inside window
 * 
 * @param room_p pointer to the room
 */
static void _draw_room(Room *room_p)
{
    int i, j, y, x;
    MLV_Color color;
    for (i = 0; i < ROOM_HEIGHT; i++)
        for (j = 0; j < ROOM_WIDTH; j++)
        {
            y = i * CELL_SIDE;
            x = j * CELL_SIDE;
            switch (room_p->cells[i][j])
            {
                /*case MANA_ON:   color = (i - j) % 2 == 0 ? MLV_COLOR_GREY20 : MLV_COLOR_GREY30;   break;*/
                case MANA_ON:   color = MLV_COLOR_GREY30;   break;
                case MANA_OFF:  color = MLV_COLOR_GREY20;   break;
                case RELIC_ON:  color = MLV_COLOR_RED;      break;
                case RELIC_OFF: color = MLV_COLOR_GREY30;   break;
                case WALL:      color = MLV_COLOR_BLACK;    break;
                case DOOR:      color = MLV_COLOR_BROWN;    break;
            }
            MLV_draw_filled_rectangle(x, y, CELL_SIDE, CELL_SIDE, color);
        }
}

/**
 * @brief Draw the player inside window
 * 
 * @param player_p pointer to the player
 */
static void _draw_player(Player *player_p)
{
    MLV_Color color;
    int win_y, win_x;
    color = player_p->overloaded ? MLV_COLOR_RED : MLV_COLOR_YELLOW;
    win_y = (int)(player_p->position.y * CELL_SIDE);
    win_x = (int)(player_p->position.x * CELL_SIDE);
    if (player_p->visible)
        MLV_draw_filled_circle(win_x, win_y, CELL_SIDE / 2, color);
    else
        MLV_draw_circle(win_x, win_y, CELL_SIDE / 2, color);
}

/**
 * @brief Draw a guard inside window
 * 
 * @param guard_p pointer to the guard
 */
static void _draw_guard(Guard *guard_p)
{
    int win_y, win_x;
    win_y = (int)(guard_p->position.y * CELL_SIDE);
    win_x = (int)(guard_p->position.x * CELL_SIDE);
    MLV_draw_filled_circle(win_x, win_y, CELL_SIDE / 2, MLV_COLOR_BLUE);
    MLV_draw_circle(win_x, win_y, CELL_SIDE * 4, MLV_COLOR_BLUE);
    /* /!\ guard range can vary */
}

/**
 * @brief Draw all guards in the array inside window
 * 
 * @param guards array containing the guards
 * @param guard_nb length of the array
 */
static void _draw_guards(Guard *guards, int guard_nb)
{
    int i;
    for (i = 0; i < guard_nb; i++)
        _draw_guard(guards + i);
}

/**
 * @brief Display remaining mana
 * 
 * @param player_p pointer to the player
 */
static void _draw_hud(Player *player_p)
{
    MLV_draw_text(0, 0, "MANA : %d", MLV_COLOR_WHITE, player_p->mana);
}

void draw_frame(Room *room_p, Player *player_p, Guard *guards)
{
    assert(room_p != NULL);
    assert(player_p != NULL);
    assert(guards != NULL);
    _draw_room(room_p);
    _draw_player(player_p);
    _draw_guards(guards, NB_GUARDS);
    _draw_hud(player_p);
    MLV_update_window();
}

void get_user_input(InputData *input_p)
{
    input_p->event = MLV_get_event(&(input_p->key), NULL, NULL,
                                   NULL, NULL,
                                   NULL, NULL, NULL,
                                   &(input_p->state));
}

static Vector draw_button(int x, int y, int imageW, int imageH, char *src){
    MLV_Image *button;
    Vector tmp;
    button = MLV_load_image(src);
    MLV_resize_image_with_proportions( button, imageW, imageH);

    MLV_draw_image(button, x, y);
    tmp.y = MLV_get_image_height(button);
    tmp.x = MLV_get_image_width(button);
    return tmp;
}

static int button_triggered(int mouse_x, int mouse_y,
                    int button_x, int button_y,
                    int buttonW, int buttonH)
{
    if(mouse_x > button_x && mouse_x < button_x + buttonW &&
        mouse_y > button_y && mouse_y < button_y + buttonH)
    {
        return 1;
    }else
    {
        return 0;
    }
}

void _draw_start_menu(void)
{
    char *welcome_text, *authors_text;
    int x, y;
    int width_text, height_text;
    int positionX, positionY;
    Vector image;

    welcome_text = "Welcome to Stealth";
    authors_text = "Game made by : CHERRATI & MESSEANT";

    MLV_get_size_of_text(welcome_text, &width_text, &height_text);
    positionX = (WINDOW_WIDTH - width_text) / 2, positionY = 100;
    MLV_draw_text(positionX, positionY, welcome_text, MLV_COLOR_GREEN);

    MLV_get_size_of_text(authors_text, &width_text, &height_text);
    positionX = 50, positionY = 800;
    MLV_draw_text(positionX, positionY, authors_text, MLV_COLOR_GREEN);
    
    image = draw_button(435, 200, 0, 0, "lib/start_button.png");
    
    MLV_actualise_window();
    while (1)
    {
        MLV_wait_mouse(&x, &y);
        if(button_triggered(x, y, 435, 200, image.x, image.y)){
            return;
        }
    }
}

int draw_quit_restart_register(int state){
    Vector quit_image, restart_image, register_image;
    int x, y;

    restart_image = draw_button(10, 10, 0, 0, "lib/play_again.png");
    quit_image = draw_button(1130, 10, 0, 0, "lib/leave.png");
    if(state){
        register_image = draw_button(550, 10, 0, 0, "lib/register.png");
    }
    MLV_actualise_window();

    MLV_wait_mouse(&x, &y);

    if(button_triggered(x, y, 10, 10, restart_image.x, restart_image.y))
    {
        return 1;
    }
    if (button_triggered(x, y, 1130, 10, quit_image.x, quit_image.y))
    {
        return 2;
    }
    if(button_triggered(x, y, 550, 10, register_image.x, register_image.y)){
        return 3;
    }
    return 0;
}

void _draw_end_win(bool *quit, bool *play, int state, bool *rgstr)
{
    int width_text, height_text;
    int positionX, positionY;
    int bt;
    
    const char *text;

    MLV_draw_filled_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, MLV_COLOR_BLACK);
    MLV_actualise_window();

    if(state){
        text = "You Won !, thank you for playing";
    }else{
        text = "You Lost !, thank you for playing";
    }
    
    MLV_get_size_of_text(text, &width_text, &height_text);

    positionX = (WINDOW_WIDTH - width_text) / 2, positionY = 400;

    MLV_draw_text(positionX, positionY, text, MLV_COLOR_RED);

    MLV_actualise_window();
    while (1)
    {
        bt = draw_quit_restart_register(state);
        if(bt == 1){
            *quit = true;
            break;
        }
        if(bt == 2){
            *play = false;
            *quit = true;
            break;
        }
        if(bt == 3){
            *rgstr = true;
            break;
        }
    }
}