#include "gba.h"
#include "box.h"
#include "ball.h"
#include "racket.h"
#include "game.h"

// ボールの現在の速度。dxは単位時間あたりのx軸向きの移動量。dyはy軸。

static fix  dx=128, dy=128;     // xとyはfix型の変数


// ボールの初期位置。
static fix x=30<<8, y=40<<8;

// ボールの位置とサイズ
static struct box my_ball = {.x = 30, .y = 40, .width = 5, .height = 5};

static struct box my_wall = {.x = 0, .y = 0, .width = LCD_WIDTH, .height = LCD_HEIGHT};

static int start;

static int key;


 // ボールのy方向の速度を返す関数
int
ball_get_dy(void) {
    return dy;
}

// ボールのy方向の速度をセットする関数
void
ball_set_dy(int new_dy) {
    dy = new_dy;
}

// ボールの箱の位置を返す関数
struct box *ball_get_box(void) {
    return &my_ball;
}

// ボールを1ステップ動かす
void
ball_step(void){
    key = gba_register(KEY_STATUS);
    switch (game_get_state()) {
        case START:
            if(start == 0){
                draw_box(&my_wall, 0, 0, COLOR_BLACK);
                start = 1;
            }
            // ボールの位置，速度を初期状態にし，ボールを表示する．
            x=30<<8, y=40<<8;
            dx=128, dy=128;
            draw_box(&my_ball, round_fix(x), round_fix(y), COLOR_WHITE);
            break;

        case RUNNING:
        // ボールのアニメーションを1ステップ行なう．
            x=x+dx;
            y=y+dy;

            if(round_fix(x)>=LCD_WIDTH-5 || round_fix(x)<=0)  {dx = -dx;} //端にぶつかったら反射
            if(round_fix(y)>=LCD_HEIGHT-5 || round_fix(y)<=0) {dy = -dy;} //端にぶつかったら反射

            // ボールがラケットに当たった時
            if(cross( &my_ball, racket_get_box() )) {
                if(round_fix(x) < racket_x()+10){
                    dx=(-128);
                }
                if(round_fix(x) > racket_x()+25){
                    dx=(128);
                }
                dy = -dy;
                y = y+dy*3;
            }

            move_box(&my_ball, round_fix(x), round_fix(y), COLOR_WHITE);

            // ボールが落ちた時
            if (round_fix(y)>=(LCD_HEIGHT-15))
                game_set_state(DEAD);

            break;

        case DEAD:
            draw_box(&my_ball, round_fix(x), round_fix(y), COLOR_WHITE); 
            break;

        case RESTART:
            // 現在のボールを画面から消し，ボールの位置，速度を初期状態にし，ボールを表示する．
            draw_box(&my_ball, round_fix(x), round_fix(y), COLOR_BLACK);
            x=30<<8, y=40<<8;
            dx=128, dy=128;
            draw_box(&my_ball, round_fix(x), round_fix(y), COLOR_WHITE);
            break;

        case CLEAR:
            draw_box(&my_ball, round_fix(x), round_fix(y), COLOR_BLACK);
            start=0;
            break;
        }
}
