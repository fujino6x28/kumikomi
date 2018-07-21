#include "gba.h"
#include "ball.h"
#include "game.h"
#include "box.h"
#include "block.h"

// staticな変数の定義
static struct box my_block = {.x = 10, .y = 5, .width = 50, .height = 10};


void
block_step(void){
    switch (game_get_state()){
        case START:
            //ブロックを表示する
            draw_box( &my_block, my_block.x , my_block.y, COLOR_WHITE);
            break;

        case RUNNING:
            if (cross( ball_get_box(), &my_block ) ){
                draw_box( &my_block, my_block.x, my_block.y, COLOR_BLACK);
                game_set_state(CLEAR);
            }

            break;

        case DEAD:
            // なにもしない
            break;

        case RESTART:
            draw_box( &my_block, my_block.x , my_block.y, COLOR_WHITE);
            break;

        case CLEAR:
            // なにもしない
            break;

    }

}
