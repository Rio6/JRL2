#include <Arduino.h>
#include <LiquidCrystal.h>

#include "config.h"
#include "functions.h"

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String msg;
float num;

void disp_init() {
   lcd.begin(16, 2);
}

void disp_num(float _num) {
   num = _num;
}

void disp_message(String _msg) {
   msg = _msg;
}

void disp_update() {
   static long last = 0;
   long now = millis();

   if(now - last > refreshInterval) {
      char buff[16];
      dtostrf(num, 8, 4, buff);

      lcd.setCursor(0, 0);
      lcd.print(msg);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print(buff);
      lcd.print("                ");
      last = now;
   }
}
