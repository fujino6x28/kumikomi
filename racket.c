#include "gba.h"
#include "box.h"
#include "ball.h"
#include "racket.h"

static int x_racket=30; //ラケットの初期位置のx座標をx_racketとし、値を30にする。
static int key; // これは筐体のキー関係で使うやつ。

static struct box my_racket = {.x = 30, .y = 135, .width = 40, .height = 5};



// ラケットの箱の位置を返す関数
struct box *racket_get_box(void) {
    return &my_racket;
}

int racket_x(void){
    return my_racket.x;
}


// ラケットを1ステップ動かす
void
racket_step(void){
    key = gba_register(KEY_STATUS);

    //左キーを押していれば左に1だけ動く
    if (! (key & KEY_LEFT)){
        x_racket = x_racket - 1;
    }
    //右キーを押していれば右に1だけ動く
    if (! (key & KEY_RIGHT)){
        x_racket = x_racket + 1;
    }

    //画面外にいかないようにする
    if(x_racket<0){
        x_racket=0;
    }
    if(LCD_WIDTH<x_racket+40){
        x_racket=LCD_WIDTH-40;
    }

    //描画更新(ラケットのy座標は135で固定)
    move_box(&my_racket, x_racket, 135, COLOR_WHITE);
}
