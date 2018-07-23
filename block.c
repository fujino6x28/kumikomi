#include "gba.h"
#include "ball.h"
#include "game.h"
#include "box.h"
#include "block.h"

// staticな変数の定義
static struct box my_block = {.x = 10, .y = 5, .width = 50, .height = 10};
static struct box my_block2 = {.x = 70, .y = 5, .width = 50, .height = 10};
static int i;

void
block_step(void){
    switch (game_get_state()){
        case START:
            //ブロックを表示する
            i=0;
            draw_box( &my_block, my_block.x, my_block.y, COLOR_WHITE);
            draw_box( &my_block2, my_block2.x, my_block2.y, COLOR_WHITE);
            break;

        case RUNNING:
            if(i==1){
                if (cross( ball_get_box(), &my_block2 ) ){
                    draw_box( &my_block2, my_block2.x, my_block2.y, COLOR_BLACK);
                    game_set_state(CLEAR);
                }
            }
            if(i==11){
                if (cross( ball_get_box(), &my_block ) ){
                    draw_box( &my_block, my_block.x, my_block.y, COLOR_BLACK);
                    game_set_state(CLEAR);
                }
            }
            if(i==0){
                if (cross( ball_get_box(), &my_block ) ){
                    draw_box( &my_block, my_block.x, my_block.y, COLOR_BLACK);
                    i+1;
                    ball_set_dy( ball_get_dy()*(-1) );
                }
                if (cross( ball_get_box(), &my_block2 ) ){
                    draw_box( &my_block2, my_block2.x, my_block2.y, COLOR_BLACK);
                    i+11;
                    ball_set_dy( ball_get_dy()*(-1) );
                }
            }
            break;





/*        case RUNNING:
            if (cross( ball_get_box(), &my_block ) ){
                if (i==1){
                    draw_box( &my_block, my_block.x, my_block.y, COLOR_BLACK);
                    game_set_state(CLEAR);
                }else{
                    draw_box( &my_block, my_block.x, my_block.y, COLOR_BLACK);
                    i++;
                    ball_set_dy( ball_get_dy()*(-1) );
                }
            }
            if (cross( ball_get_box(), &my_block2 ) ){
                if (i==1){
                    draw_box( &my_block2, my_block2.x, my_block2.y, COLOR_BLACK);
                    game_set_state(CLEAR);
                }else{
                    draw_box( &my_block2, my_block2.x, my_block2.y, COLOR_BLACK);
                    i++;
                    ball_set_dy( ball_get_dy()*(-1) );
                }
            }
            break;
*/

        case DEAD:
            // なにもしない
            break;

        case RESTART:
            draw_box( &my_block, my_block.x , my_block.y, COLOR_WHITE);
            draw_box( &my_block2, my_block2.x , my_block2.y, COLOR_WHITE);
            break;

        case CLEAR:
            // なにもしない
            break;

    }

}
