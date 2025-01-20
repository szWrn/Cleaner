#include <U8g2lib.h>

struct menu {
    char* name;
    char* value;
    void (*action)();
};

void display(menu menus[], U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2);
void up();
void down();
void onClick(menu menus[]);