#include "gba.h"

main()
{
    hword   *fb = (hword*)VRAM;
    int     x, y;
    
    /* Initialize LCD Control Register to use Mode 3. */
    gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;
    
    /* Put 10 dots from (10, 10) to (10, 19). */
     for (x = 10, y = 10; x < 150; x++) {
         *(fb + (LCD_WIDTH * y) + x) = BGR(0x00, 0x1F, 0x00);
     }
    
    for (x = 10, y = 150; x < 150; x++) {
        *(fb + (LCD_WIDTH * y) + x) = BGR(0x00, 0x1F, 0x00);
    }
    
    for (x = 10, y = 10; y < 150; y++) {
        *(fb + (LCD_WIDTH * y) + x) = BGR(0x00, 0x1F, 0x00);
    }
    
    for (x = 150, y = 10; y < 150; y++) {
        *(fb + (LCD_WIDTH * y) + x) = BGR(0x00, 0x1F, 0x00);
    }
    
    
    /* spin forever here */
    for (;;) {}
}
