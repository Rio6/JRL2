#pragma once

#include <EEPROM.h>
#include <BasicLinearAlgebra.h>

using namespace BLA;

static void printEquation(const Matrix<4, 1> &cal) {
   char buff[16];

   dtostrf(cal(0), 10, 10, buff);
   Serial.print(buff);
   Serial.print("x^3 + ");
   dtostrf(cal(1), 10, 10, buff);
   Serial.print(buff);
   Serial.print("x^2 + ");
   dtostrf(cal(2), 10, 10, buff);
   Serial.print(buff);
   Serial.print("x + ");
   dtostrf(cal(3), 10, 10, buff);
   Serial.println(buff);
}

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
   Matrix<4, 1> cal;

   void loadFromEEPROM() {
      for(int i = 0; i < 4; i++) {
         EEPROM.get(i * sizeof(float), cal(i));
      }
      n = N;
      Serial.println("loaded");
      printEquation(cal);
   }

   void saveToEEPROM() {
      Serial.println("saving");
      printEquation(cal);
      for(int i = 0; i < 4; i++) {
         EEPROM.put(i * sizeof(float), cal(i));
      }
   }

   void reset() {
      n = 0;
   }

   void update(float x) {
      if(!calibrating()) return;
      float y = nexty();

      Serial.print("x: ");
      Serial.print(x);
      Serial.print(", y: ");
      Serial.println(y);

      xs(n, 0) = x*x*x;
      xs(n, 1) = x*x;
      xs(n, 2) = x;
      xs(n, 3) = 1;
      ys(n) = y;
      n++;

      if(n == N) {
         auto proj = ~xs * xs;
         Invert(proj);
         cal = proj * ~xs * ys;
         saveToEEPROM();
      }
   }

   bool calibrating() {
      return n < N;
   }

   float calibrate(float v) {
      Matrix<1, 4> row = { v*v*v, v*v, v, 1 };
      return (row * cal)(0);
   }

   float nexty() {
      return calPoints[n % N];
   }
};
