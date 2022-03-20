#include <Arduino.h>

#include "config.h"
#include "functions.h"

static int num = 0;

static int num_digit(int num, int digit) {
   for(int i = 0; i < digit; i++) {
      num /= 10;
   }
   return num % 10;
}

void disp_init() {
   pinMode(a, OUTPUT);     
   pinMode(b, OUTPUT);     
   pinMode(c, OUTPUT);     
   pinMode(d, OUTPUT);     
   pinMode(e, OUTPUT);     
   pinMode(f, OUTPUT);     
   pinMode(g, OUTPUT);   
   pinMode(d1, OUTPUT);  
   pinMode(d2, OUTPUT);  
   pinMode(d3, OUTPUT);  
   pinMode(d4, OUTPUT);
   pinMode(p, OUTPUT);

   digitalWrite(p, HIGH);
}

void disp_num(int _num) {
   num = _num;
}

void disp_update() {
   static int digit = 0;
   disp_digit(digit, num_digit(num, digit));
   digit = (digit + 1) % 4;
}

void disp_digit(int digit, int num) {
   digitalWrite(d1, LOW);
   digitalWrite(d2, LOW);
   digitalWrite(d3, LOW);
   digitalWrite(d4, LOW);
   switch(digit) {
      case 0:
         digitalWrite(d4, HIGH);
         break;
      case 1:
         digitalWrite(d3, HIGH);
         break;
      case 2:
         digitalWrite(d2, HIGH);
         break;
      case 3:
         digitalWrite(d1, HIGH);
         break;  
   }
   switch(num) {
      default:
         digitalWrite(a, HIGH);
         digitalWrite(b, HIGH);
         digitalWrite(c, HIGH);
         digitalWrite(d, HIGH);
         digitalWrite(e, HIGH);
         digitalWrite(f, HIGH);
         digitalWrite(g, HIGH);
         break;
      case 0: 
         digitalWrite(a, LOW);
         digitalWrite(b, LOW);
         digitalWrite(c, LOW);
         digitalWrite(d, LOW);
         digitalWrite(e, LOW);
         digitalWrite(f, LOW);
         digitalWrite(g, HIGH);
         break;
      case 1: 
         digitalWrite(a, HIGH);
         digitalWrite(b, LOW);
         digitalWrite(c, LOW);
         digitalWrite(d, HIGH);
         digitalWrite(e, HIGH);
         digitalWrite(f, HIGH);
         digitalWrite(g, HIGH);
         break;
      case 2: 
         digitalWrite(a, LOW);
         digitalWrite(b, LOW);
         digitalWrite(c, HIGH);
         digitalWrite(d, LOW);
         digitalWrite(e, LOW);
         digitalWrite(f, HIGH);
         digitalWrite(g, LOW);
         break;
      case 3: 
         digitalWrite(a, LOW);
         digitalWrite(b, LOW);
         digitalWrite(c, LOW);
         digitalWrite(d, LOW);
         digitalWrite(e, HIGH);
         digitalWrite(f, HIGH);
         digitalWrite(g, LOW);
         break;
      case 4: 
         digitalWrite(a, HIGH);
         digitalWrite(b, LOW);
         digitalWrite(c, LOW);
         digitalWrite(d, HIGH);
         digitalWrite(e, HIGH);
         digitalWrite(f, LOW);
         digitalWrite(g, LOW);
         break;
      case 5: 
         digitalWrite(a, LOW);
         digitalWrite(b, HIGH);
         digitalWrite(c, LOW);
         digitalWrite(d, LOW);
         digitalWrite(e, HIGH);
         digitalWrite(f, LOW);
         digitalWrite(g, LOW);
         break;
      case 6: 
         digitalWrite(a, LOW);
         digitalWrite(b, HIGH);
         digitalWrite(c, LOW);
         digitalWrite(d, LOW);
         digitalWrite(e, LOW);
         digitalWrite(f, LOW);
         digitalWrite(g, LOW);
         break;
      case 7: 
         digitalWrite(a, LOW);
         digitalWrite(b, LOW);
         digitalWrite(c, LOW);
         digitalWrite(d, HIGH);
         digitalWrite(e, HIGH);
         digitalWrite(f, HIGH);
         digitalWrite(g, HIGH);
         break;
      case 8: 
         digitalWrite(a, LOW);
         digitalWrite(b, LOW);
         digitalWrite(c, LOW);
         digitalWrite(d, LOW);
         digitalWrite(e, LOW);
         digitalWrite(f, LOW);
         digitalWrite(g, LOW);
         break;
      case 9: 
         digitalWrite(a, LOW);
         digitalWrite(b, LOW);
         digitalWrite(c, LOW);
         digitalWrite(d, LOW);
         digitalWrite(e, HIGH);
         digitalWrite(f, LOW);
         digitalWrite(g, LOW); 
         break;
   }
   delay(5);
} 
