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

menu menus[6] = {
  {"Fan", "Off", nullptr},
  {"UV", "Off", UV},
  {"Fan 3", "Off", nullptr},
  {"Fan 4", "Off", nullptr},
  {"Fan 5", "Off", nullptr},
  {"Fan 6", "Off", nullptr}
};

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  pinMode(fansPin1, OUTPUT);
  pinMode(fansPin2, OUTPUT);
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
  // if (digitalRead(selectPin) == LOW) {
  //   onClick(menus);
  //   delay(100);
  // }
  fan = 0;
  if (digitalRead(backPin) == LOW) {
    fan = 1;
    delay(80);
  }
  if (digitalRead(forwardPin) == LOW) {
    fan = -1;
    delay(80);
  }
  if (fan == 1) {
    digitalWrite(fansPin2, HIGH);
    digitalWrite(fansPin1, LOW);
  }
  if (fan == -1) {
    digitalWrite(fansPin1, HIGH);
    digitalWrite(fansPin2, LOW);
  }
  if (fan == 0) {
    digitalWrite(fansPin1, HIGH);
    digitalWrite(fansPin2, HIGH);
  }
}