#include <Arduino.h>

enum states { gnd, low, high };

#define D_NEGATIVE_680 1
#define D_NEGATIVE_2k 2
#define D_POSITIVE_680 3
#define D_POSITIVE_2k 4

void set_data_line_voltage(bool pin, states state) {
  // true = positive, false = negative
  int pin_a = pin ? D_POSITIVE_680 : D_NEGATIVE_680;
  int pin_b = pin ? D_POSITIVE_2k : D_NEGATIVE_2k;

  if (state == low) {
    digitalWrite(pin_a, false);
    digitalWrite(pin_b, true);
  }
  if (state == high) {
    digitalWrite(pin_a, true);
    digitalWrite(pin_b, false);
  }
  if (state == gnd) {
    digitalWrite(pin_a, false);
    digitalWrite(pin_b, false);
  }
}

void initialize() {
  pinMode(D_NEGATIVE_680, INPUT);
  pinMode(D_NEGATIVE_2k, INPUT);
  pinMode(D_POSITIVE_680, OUTPUT);
  pinMode(D_POSITIVE_2k, OUTPUT);

  set_data_line_voltage(1, low);
  
  //digitalWrite(D_POSITIVE_2k, true);
  //digitalWrite(D_POSITIVE_680, false);

  delay(2000);

  pinMode(D_NEGATIVE_680, OUTPUT);
  pinMode(D_NEGATIVE_2k, OUTPUT);

  //digitalWrite(D_NEGATIVE_2k, true);
  //digitalWrite(D_NEGATIVE_680, false);
}

void set_5v() { // Keeps previous status
  set_data_line_voltage(0, gnd);
  set_data_line_voltage(1, low);
}

void set_9v() {
  set_data_line_voltage(0, low);
  set_data_line_voltage(1, high);
}
void set_12v() {
  set_data_line_voltage(0, low);
  set_data_line_voltage(1, low);
}

void setup() {
  initialize(); 
  set_12v();
}

void loop() {
  set_12v();
  delay(2000);
  set_9v();
  delay(2000);
  set_5v();
  delay(2000);
}
