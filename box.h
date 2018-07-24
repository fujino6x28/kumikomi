struct box {
    int     x, y;
    int     width, height;
};

#define COLOR_WHITE     BGR(31, 31, 31)
#define COLOR_BLACK     0
#define FONT_SIZE       8
typedef  int  fix;    // fix型という名前をつける．

extern void draw_box(struct box *b, int x, int y, hword color);
extern void move_box(struct box *b, int x, int y, hword color);
extern int cross(struct box *b1, struct box *b2);
extern int round_fix(fix f);
