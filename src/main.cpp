#include <Arduino.h>

#define USE_TIMER_2 true
#include <TimerInterrupt.h>

#include "config.h"
#include "functions.h"
#include "sample.h"

static Sampler<numSamples> value;
static Calibrator<numCals> cal;

void sample() {
   value.update(analogRead(input));
}

void setup() {
   analogReference(EXTERNAL);

   Serial.begin(9600);

   // button
   pinMode(btn, INPUT_PULLUP);

   // sensor
   pinMode(input, INPUT);
   pinMode(inputpwr, OUTPUT);
   pinMode(inputgnd, OUTPUT);

   digitalWrite(inputpwr, HIGH);
   digitalWrite(inputgnd, LOW);

   // display
   disp_init();

   // sample timer
   ITimer2.init();
   ITimer2.attachInterrupt(sampleFreq, sample);

   // load saved calibration
   cal.loadFromEEPROM();
}

void loop() {
   long now = millis();

   if(cal.calibrating()) {
      disp_message("Calibrating");
      disp_num(cal.nexty());
   } else {
      disp_message("Measuring");
      disp_num(cal.calibrate(value));
      Serial.println(value.value());
   }

   disp_update();

   // button
   static long btnon = 0;
   if(!digitalRead(btn)) {
      if(!btnon) {
         btnon = now;
      }
   } else {
      if(btnon) {
         // long hold
         if(now - btnon > 1000) {
            cal.reset();
         }

         // short release
         else if(now - btnon > 100) {
            cal.update(value);
         }
      }

      btnon = 0;
   }
}
