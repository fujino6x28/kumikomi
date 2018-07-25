#include "gba.h"
#include "game.h"
#include "box.h"
#include "8x8.til"

static enum state current_state;  // 現在の状態
static int key;
static int i;
static struct box my_wall = {.x = 40, .y = 60, .width = 150, .height = 30};

enum state game_get_state(void) { return current_state; }

void
game_set_state(enum state new_state) {
  current_state = new_state;
}

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

void
game_step(void){
    key = gba_register(KEY_STATUS);
    hword   *fb = (hword*)VRAM;
    switch (game_get_state()) {
        case START:
            i=0;
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2-56, COLOR_WHITE, 'P');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2-46, COLOR_WHITE, 'R');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2-36, COLOR_WHITE, 'E');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2-26, COLOR_WHITE, 'S');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2-16, COLOR_WHITE, 'S');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2+4, COLOR_WHITE, 'S');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2+14, COLOR_WHITE, 'T');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2+24, COLOR_WHITE, 'A');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2+34, COLOR_WHITE, 'R');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2+44, COLOR_WHITE, 'T');
            if (! (key & KEY_START))
                game_set_state(RUNNING);
            break;

        case RUNNING:
            if (i==0){
                draw_box(&my_wall, my_wall.x, my_wall.y, COLOR_BLACK);
                i=1;
            }
            //何もしない。

            //ズル機能(いちおう開発用)
            if (! (key & KEY_SELECT))
                game_set_state(CLEAR);
            break;

        case DEAD:
            if (! (key & KEY_START))
                game_set_state(RESTART);
            break;

        case RESTART:
            // 次のティックはRUNNING状態にする
            game_set_state(RUNNING);
            break;

        case CLEAR:
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2-26, COLOR_WHITE, 'C');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2-16, COLOR_WHITE, 'L');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2-6, COLOR_WHITE, 'E');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2+4, COLOR_WHITE, 'A');
            draw_char(fb+(LCD_WIDTH * (LCD_HEIGHT/2)) + LCD_WIDTH/2+14, COLOR_WHITE, 'R');

            if (! (key & KEY_START))
            game_set_state(START);
            break;
  }
}
