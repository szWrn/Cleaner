#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <pins.h>
#include <menu.h>

menu menus[2] = {
  {"Fan", "Off", "On", fanPin, 0},
  {"UV", "Off", "On", UVPin, 0}
};

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  // Serial.begin(9600);
  pinMode(fanPin, OUTPUT);
  pinMode(UVPin, OUTPUT);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  #ifdef button
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  pinMode(selectPin, INPUT);
  pinMode(backPin, INPUT);
  pinMode(forwardPin, INPUT);
  #endif
  #ifdef rotary
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(selectPin, INPUT);
  #endif
}

void loop() {
  // Serial.println(digitalRead(selectPin));
  display(menus, u8g2);
  #ifdef button
  if (digitalRead(upPin) == LOW) {
    up();
    delay(100);
  }
  if (digitalRead(downPin) == LOW) {
    down();
    delay(100);
  }
  #endif
  #ifdef rotary
  if (analogRead(xPin) == 1023) {
    up();
    delay(100);
  }
  if (analogRead(xPin) == 0) {
    down();
    delay(100);
  }
  #endif
  if (digitalRead(selectPin) == LOW) {
    onClick(menus);
    delay(100);
  }
  // fan = 0;
  // // if (digitalRead(backPin) == LOW && menus[0].state == 1) {
  // //   fan = 1;
  // //   delay(80);
  // // }
  // if (digitalRead(backPin) == LOW) {
  //   fan = 1;
  //   delay(80);
  // }
  // // if (digitalRead(forwardPin) == LOW && menus[0].state == 1) {
  // //   fan = -1;
  // //   delay(80);
  // // }
  // if (digitalRead(forwardPin) == LOW) {
  //   fan = -1;
  //   delay(80);
  // }
}