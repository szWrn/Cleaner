#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <pins.h>
#include <menu.h>

int page = 0;
int fan = 0;
int uv = 0;

void changePage(int p) {
  page = p;
}

void UV() {
  if (uv == 0) {
    uv = 1;
    digitalWrite(UVPin, HIGH);
  } else {
    uv = 0;
    digitalWrite(UVPin, LOW);
  }
}

menu menus[3] = {
  {"Fan", "Off", "On", fanPin, 0},
  {"UV", "Off", "On", UVPin, 0},
  {"Fan 3", "Off", "On", -1, 0}
};

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  pinMode(fanPin, OUTPUT);
  pinMode(UVPin, OUTPUT);
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  pinMode(selectPin, INPUT);
  pinMode(backPin, INPUT);
  pinMode(forwardPin, INPUT);
  digitalWrite(6, HIGH); // Enable pull-down resistor
  digitalWrite(7, HIGH);
}

void loop() {
  display(menus, u8g2);
  if (digitalRead(upPin) == LOW) {
    up();
    delay(80);
  }
  if (digitalRead(downPin) == LOW) {
    down();
    delay(80);
  }
  if (digitalRead(selectPin) == LOW) {
    onClick(menus);
    delay(80);
  }
  fan = 0;
  // if (digitalRead(backPin) == LOW && menus[0].state == 1) {
  //   fan = 1;
  //   delay(80);
  // }
  if (digitalRead(backPin) == LOW) {
    fan = 1;
    delay(80);
  }
  // if (digitalRead(forwardPin) == LOW && menus[0].state == 1) {
  //   fan = -1;
  //   delay(80);
  // }
  if (digitalRead(forwardPin) == LOW) {
    fan = -1;
    delay(80);
  }
}