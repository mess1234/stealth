#include <stdio.h>
#include <stdlib.h>

#include "../include/score.h"
#include "../include/frontend.h"

void record_data(int player_mana, double time_spent){
    FILE *out;
    Game_score gs, gs2[10];
    char *name;
    int k, i;
    
    MLV_draw_filled_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, MLV_COLOR_BLACK);
    MLV_actualise_window();
    
    out = fopen("data/score.bin", "ab+");
    if (out == NULL){
       printf("Error opening file \n");
    }
    /*affichage de la liste des 10 derniers enregistrement*/
    i = fread(gs2, sizeof(Game_score), 10, out);
    MLV_draw_text(35, 100, "TOP 10 : ", MLV_COLOR_WHITE);
    for(k = 0; k < i; k++){
        MLV_draw_text(35, 120 + (15*k), "name : %s | mana : %d | temps passe : %ld", MLV_COLOR_WHITE,
                    gs2[k].name, gs2[k].mana, gs2[k].time_spent
                    );
    }

    MLV_wait_input_box(435, 200, 535, 300,
                        MLV_COLOR_RED, MLV_COLOR_WHITE, MLV_COLOR_BLACK,
                        "Saissisez votre nom pour l'enregistrement du score : ",
                        &name);

    strcpy(gs.name , name);
    gs.mana = player_mana; /* on prend le nb_mana du joueur*/
    gs.time_spent = time_spent;
    fwrite(&gs, sizeof(Game_score), 1, out); 
    
    fclose(out); 
    free (name);
    return;
}
