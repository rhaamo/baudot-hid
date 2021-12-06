#include <Arduino.h>
#include "BaudotDecoder.h"
#include <Bounce.h>

#define KEY_PRESSED 5 // INT0
#define BAUDOT_1 A0
#define BAUDOT_2 A1
#define BAUDOT_3 A2
#define BAUDOT_4 A3
#define BAUDOT_5 A4

#define LED A10

Bounce trigger = Bounce(KEY_PRESSED, 10);

enum levels { LEVEL_LOW, LEVEL_HIGH };
bool activeLevel = LEVEL_LOW;
int baudotCode[5] = { 0, 0, 0, 0, 0 };

void decodeBaudot() {
  // When the key is fully pressed (so all the bars are in position), a switch is activated
  // Serial.print("Attempting to decode code: '");
  // Serial.print(baudotCode[0]);
  // Serial.print(baudotCode[1]);
  // Serial.print(baudotCode[2]);
  // Serial.print(baudotCode[3]);
  // Serial.print(baudotCode[4]);
  // Serial.println("'");
  BaudotDecoder::convertBitsToChar(baudotCode);
}

void setup() {
  Serial.begin(9600);
  Keyboard.begin();

  Serial.println("Baudot-HID");

  pinMode(KEY_PRESSED, INPUT_PULLUP);

  pinMode(BAUDOT_1, INPUT_PULLUP);
  pinMode(BAUDOT_2, INPUT_PULLUP);
  pinMode(BAUDOT_3, INPUT_PULLUP);
  pinMode(BAUDOT_4, INPUT_PULLUP);
  pinMode(BAUDOT_5, INPUT_PULLUP);

  pinMode(LED, OUTPUT);

  //attachInterrupt(digitalPinToInterrupt(KEY_PRESSED), decodeBaudot, FALLING);

}

void loop() {
  // Read all the pins
  // needs to invert the reading because of the pullup
  baudotCode[0] = !digitalRead(BAUDOT_1);
  baudotCode[1] = !digitalRead(BAUDOT_2);
  baudotCode[2] = !digitalRead(BAUDOT_3);
  baudotCode[3] = !digitalRead(BAUDOT_4);
  baudotCode[4] = !digitalRead(BAUDOT_5);
  trigger.update();
  if (trigger.fallingEdge()) {
    decodeBaudot();
  }
}
