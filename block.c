#include "gba.h"
#include "ball.h"
#include "game.h"
#include "box.h"
#include "block.h"
//#include "8x8.til"

// staticな変数の定義
static struct box my_block1 = {.x = 5, .y = 5, .width = 50, .height = 10};
static struct box my_block2 = {.x = 65, .y = 5, .width = 50, .height = 10};
static struct box my_block3 = {.x = 125, .y = 5, .width = 50, .height = 10};
static struct box my_block4 = {.x = 185, .y = 5, .width = 50, .height = 10};
static struct box my_block5 = {.x = 5, .y = 25, .width = 50, .height = 10};
static struct box my_block6 = {.x = 65, .y = 25, .width = 50, .height = 10};
static struct box my_block7 = {.x = 125, .y = 25, .width = 50, .height = 10};
static struct box my_block8 = {.x = 185, .y = 25, .width = 50, .height = 10};


static int num_blocks;

static int i1,i2,i3,i4,i5,i6,i7,i8;

/*
void
draw_char(hword *ptr, hword color, int code){
    hword *p;
    int i,j;
    unsigned char *font = char8x8[code];
    for (i=0; i<FONT_SIZE; i++){
        p = ptr + LCD_WIDTH * i;
        for (j=FONT_SIZE-1; j>=0; j--, p++){
            if(font[i]&(1<<j))
                *p = color;
        }
    }
}
*/

void
block_step(void){
//    hword   *fb = (hword*)VRAM;
    switch (game_get_state()){
        case START:
            //ブロックを表示する
            num_blocks=0;
            i1=i2=i3=i4=i5=i6=i7=i8=0;
            draw_box( &my_block1, my_block1.x, my_block1.y, COLOR_WHITE);
            draw_box( &my_block2, my_block2.x, my_block2.y, COLOR_WHITE);
            draw_box( &my_block3, my_block3.x, my_block3.y, COLOR_WHITE);
            draw_box( &my_block4, my_block4.x, my_block4.y, COLOR_WHITE);
            draw_box( &my_block5, my_block5.x, my_block5.y, COLOR_WHITE);
            draw_box( &my_block6, my_block6.x, my_block6.y, COLOR_WHITE);
            draw_box( &my_block7, my_block7.x, my_block7.y, COLOR_WHITE);
            draw_box( &my_block8, my_block8.x, my_block8.y, COLOR_WHITE);
            break;

        case RUNNING:
            if(i1==0){
                if (cross( ball_get_box(), &my_block1 ) ){
                    draw_box( &my_block1, my_block1.x, my_block1.y, COLOR_BLACK);
                    i1=1;
                    num_blocks=num_blocks+1;
                    ball_set_dy( ball_get_dy()*(-1) );
                }
            }
            if(i2==0){
                if (cross( ball_get_box(), &my_block2 ) ){
                    draw_box( &my_block2, my_block2.x, my_block2.y, COLOR_BLACK);
                    i2=1;
                    num_blocks=num_blocks+1;
                    ball_set_dy( ball_get_dy()*(-1) );
                }
            }
            if(i3==0){
                if (cross( ball_get_box(), &my_block3 ) ){
                    draw_box( &my_block3, my_block3.x, my_block3.y, COLOR_BLACK);
                    i3=1;
                    num_blocks=num_blocks+1;
                    ball_set_dy( ball_get_dy()*(-1) );
                }
            }
            if(i4==0){
                if (cross( ball_get_box(), &my_block4 ) ){
                    draw_box( &my_block4, my_block4.x, my_block4.y, COLOR_BLACK);
                    i4=1;
                    num_blocks=num_blocks+1;
                    ball_set_dy( ball_get_dy()*(-1) );
                }
            }
            if(i5==0){
                if (cross( ball_get_box(), &my_block5 ) ){
                    draw_box( &my_block5, my_block5.x, my_block5.y, COLOR_BLACK);
                    i5=1;
                    num_blocks=num_blocks+1;
                    ball_set_dy( ball_get_dy()*(-1) );
                }
            }
            if(i6==0){
                if (cross( ball_get_box(), &my_block6 ) ){
                    draw_box( &my_block6, my_block6.x, my_block6.y, COLOR_BLACK);
                    i6=1;
                    num_blocks=num_blocks+1;
                    ball_set_dy( ball_get_dy()*(-1) );
                }
            }
            if(i7==0){
                if (cross( ball_get_box(), &my_block7 ) ){
                    draw_box( &my_block7, my_block7.x, my_block7.y, COLOR_BLACK);
                    i7=1;
                    num_blocks=num_blocks+1;
                    ball_set_dy( ball_get_dy()*(-1) );
                }
            }
            if(i8==0){
                if (cross( ball_get_box(), &my_block8 ) ){
                    draw_box( &my_block8, my_block8.x, my_block8.y, COLOR_BLACK);
                    i8=1;
                    num_blocks=num_blocks+1;
                    ball_set_dy( ball_get_dy()*(-1) );
                }
            }
            if(num_blocks==8){
                game_set_state(CLEAR);
            }

            break;


        case DEAD:
            // なにもしない
            break;

        case RESTART:
            // なにもしない
            break;

        case CLEAR:
            //CLEARと表示

/*            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2-26, COLOR_WHITE, 'C');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2-16, COLOR_WHITE, 'L');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2-6, COLOR_WHITE, 'E');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2+4, COLOR_WHITE, 'A');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2+14, COLOR_WHITE, 'R');
*/
            break;

    }

}
