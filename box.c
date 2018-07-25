#include "gba.h"
#include "box.h"

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



// 四角を動かす。前に書いた四角を黒で塗りつぶし、新しい場所に四角を書く。
void
move_box(struct box *b, int x, int y, hword color){
    draw_box(b, b->x, b->y, COLOR_BLACK);
    draw_box(b, x, y, color);
}



// 2つの箱が画面上で重なっているかどうかを判定する関数
int cross(struct box *b1, struct box *b2){
    // b1とb2の領域が重なっていれば1，重なっていなければ0を返す．
    if((b2->x<=(b1->x+b1->width))&&(b1->x<=(b2->x+b2->width)) &&
    ((b2->y<=(b1->y+b1->height))&&(b1->y<=(b2->y+b2->height)))){
        return(1);
    }
    return(0);
}
