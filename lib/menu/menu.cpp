#include <menu.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <Arduino.h>

int choice = 1;
void display(menu menus[], U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB14_tr);
    for (int i = 0; i < 6; i++) {
        if (choice == i) {
            u8g2.setDrawColor(1);
            u8g2.drawBox(0, i * 16, 128, 10);
            u8g2.setDrawColor(0);
        } else {
            u8g2.setDrawColor(1);
        }
        u8g2.drawStr(0, 16 + i * 16, menus[i].name);
        u8g2.drawStr(100, 16 + i * 16, menus[i].value);
    }
    u8g2.sendBuffer();
}

void up() {
    if (choice >= 5) choice = 0;
    else choice ++;
}

void down() {
    if (choice <= 0) choice = 6;
    else choice --;
}

void onClick(menu menus[]) {
    if (menus[choice].selected != NULL) {
        char* v = menus[choice].value;
        menus[choice].value = menus[choice].selected;
        menus[choice].selected = v;
    }
    if (menus[choice].state == 0) menus[choice].state = 1;
    else menus[choice].state = 0;
    if (menus[choice].pin != -1) digitalWrite(menus[choice].pin, menus[choice].state == 0 ? LOW : HIGH);
}