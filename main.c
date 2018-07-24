#include "gba.h"
#include "ball.h"
#include "box.h"
#include "racket.h"
#include "game.h"
#include "block.h"

int round_fix(fix f) {
     return (f + 0x80) >> 8;
  }


// 速度の調整
void
delay(hword val){
    val += gba_register(TMR_COUNT0);
    while (val != gba_register(TMR_COUNT0));
}


void
main(){
//    hword   *fb = (hword*)VRAM;
//    int     x, y;


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
