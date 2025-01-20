#include <menu.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <Arduino.h>

int choice = 0;

void display(menu menus[], U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    for (int i = 0; i < 10; i++) {
        if (choice == i) {
            u8g2.setDrawColor(1);
            u8g2.drawBox(0, i * 10, 128, 10);
            u8g2.setDrawColor(0);
        } else {
            u8g2.setDrawColor(1);
        }
        u8g2.drawStr(0, 10 + i * 10, menus[i].name);
        u8g2.drawStr(100, 10 + i * 10, menus[i].value);
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
    if (menus[choice].action != NULL) {
        menus[choice].action();
    }
}