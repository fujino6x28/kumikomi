#include "gba.h"
#include "ball.h"
#include "box.h"
#include "racket.h"
#include "game.h"
#include "block.h"

int round_fix(fix f) {
     return (f + 0x80) >> 8;
  }


/* box.hに移動
struct box {
    int     x, y;
    int     width, height;
};
*/


/* box.cに移動
// 四角を表示する。左上が(x,y)でそこからの幅(width)と高さ(height)。
void
draw_box(struct box *b, int x, int y, hword color){
     hword   *base, *d;
     int     w, h;

     // Base point is at (x, y).
     base = (hword*)VRAM + LCD_WIDTH * y + x;

     // Draw box from (x, y).
     for (h = b->height; h > 0; h--) {
        d = base;
        for (w = b->width; w > 0; w--)
            *(d++) = color;
        base += LCD_WIDTH;
    }

    // Set the current position.
    b->x = x;
    b->y = y;
}
*/


/* box.cに移動
// 四角を動かす。前に書いた四角を黒で塗りつぶし、新しい場所に四角を書く。
void
move_box(struct box *b, int x, int y, hword color){
    draw_box(b, b->x, b->y, COLOR_BLACK);
    draw_box(b, x, y, color);
}
*/

/* これはいらんかもしれん。
// 速度の調整。wait(数字)で、数字が大きいほど速度が遅くなる。
void
wait(int val) {
        int     i, j;

        for (i = 0; i < val; i++)
                for (j = 0; j < val; j++)
                        ;
}
*/

// 速度の調整(上級編)
void
delay(hword val){
    val += gba_register(TMR_COUNT0);
    while (val != gba_register(TMR_COUNT0));
}



main(){
    hword   *fb = (hword*)VRAM;
    int     x, y;


    // 画面を初期化 (なんかわからんけどこれで動く)
    /* Initialize LCD Control Register to use Mode 3. */
    gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;


    // タイマーを初期化 (よくわからんがこのままで動くので触らんでいい)
    /* Initialize Timer 0. */
    gba_register(TMR_COUNT0) = 0;
    gba_register(TMR_CTRL0) = TMR_ENABLE + TMR_1024CLOCK;


    while (1) {
        // ボールを1ステップ動かす(ball.cに記述)
        ball_step();

        // ラケットを1ステップ動かす(racket.cに記述)
        racket_step();

        block_step();

        // ゲームの状態の管理(game.cに記述)
        game_step();



        int state = game_get_state();
        int count = 0;
        while(state){
            if(state % 2 == 0){
                gba_register(VRAM + LCD_WIDTH * (LCD_HEIGHT - 1) - count + LCD_WIDTH - 1) = COLOR_BLACK;
            }else{
                gba_register(VRAM + LCD_WIDTH * (LCD_HEIGHT - 1) - count + LCD_WIDTH - 1) = COLOR_WHITE;
            }
            state /= 2;
            count++;
        }
        // delay()で待つ
        delay(50);
    }
}
