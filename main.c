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


int
main(){

    // 画面を初期化
    /* Initialize LCD Control Register to use Mode 3. */
    gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;

    // タイマーを初期化
    /* Initialize Timer 0. */
    gba_register(TMR_COUNT0) = 0;
    gba_register(TMR_CTRL0) = TMR_ENABLE + TMR_1024CLOCK;


    while (1) {
        // ボールを1ステップ動かす(ball.cに記述)
        ball_step();

        // ラケットを1ステップ動かす(racket.cに記述)
        racket_step();

        // ブロックの挙動(block.cに記述)
        block_step();

        // ゲームの状態の管理(game.cに記述)
        game_step();

        // ゲームのstateを見るために画面右下に小さい点を表示しておく(開発用)
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

        // 速度調整のため
        delay(50);
    }
}
