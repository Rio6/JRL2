#include <Arduino.h>
#include <BasicLinearAlgebra.h>

#include "config.h"
#include "functions.h"

using namespace BLA;

static constexpr int numSamples = 20;
static constexpr int numCals = 6;

template <int N>
struct Sampler {
   int samples[N];
   int index = 0;

   void update(int v) {
      samples[index] = v;
      index = (index + 1) % N;
   }

   float value() {
      float avg = 0;
      for(int i = 0; i < N; i++) {
         avg += samples[i];
      }
      return avg / N;
   }

   operator float() {
      return value();
   }
};

template <int N>
struct Calibrator {
   int n = 0;
   Matrix<N, 4> xs;
   Matrix<N, 1> ys;

   void reset() {
      n = 0;
   }

   void update(float x) {
      if(!calibrating()) return;
      xs(n, 0) = x*x*x;
      xs(n, 1) = x*x;
      xs(n, 2) = x;
      xs(n, 3) = 1;
      ys(n) = nexty();
      n++;
   }

   bool calibrating() {
      return n < N;
   }

   float calibrate(float v) {
      Matrix<1, 4> row = { v*v*v, v*v, v, 1 };
      return row * Invert(~xs * xs) * ~xs * ys;
   }

   float nexty() {
      return maxDist / (N - 1) * n;
   }
};

void setup() {
   pinMode(btn, INPUT);
   pinMode(input, INPUT);
   disp_init();
}

void loop() {
   long now = millis();

   static Sampler<numSamples> value;
   static Calibrator<numCals> cal;

   value.update(analogRead(input));

   // sample
   if(cal.calibrating()) {
      disp_num(cal.nexty());
   } else {
      disp_num(value);
   }

   disp_update();

   // button
   static long btnon = 0;
   bool pressed = analogRead(btn) < 0x200;

   if(pressed && !btnon) {
      btnon = now;
   }

   // short release
   if(!pressed) {
      if(btnon && now - btnon > 100) {
         cal.update(value);
      }
      btnon = 0;
   }

   // long hold
   if(pressed && btnon && now - btnon > 1000) {
      cal.reset();
      btnon = 0;
   }
}
