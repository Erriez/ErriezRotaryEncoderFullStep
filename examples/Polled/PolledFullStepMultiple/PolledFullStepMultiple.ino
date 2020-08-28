/*
 * MIT License
 *
 * Copyright (c) 2018-2020 Erriez
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* Example multiple polled full step Rotary Encoders
 * Source:         https://github.com/Erriez/ErriezRotaryEncoderFullStep
 * Documentation:  https://erriez.github.io/ErriezRotaryEncoderFullStep
 */

#include <ErriezRotaryFullStep.h>

// Connect rotary pins to the DIGITAL or ANALOG pins of the Arduino board
// Use A0..A7 when using analog pins
#define ROTARY1_PIN1        2
#define ROTARY1_PIN2        3
#define ROTARY1_BUTTON_PIN  4
#define ROTARY2_PIN1        5
#define ROTARY2_PIN2        6
#define ROTARY2_BUTTON_PIN  7

// Configure a number of rotaries
#define NUM_ROTARIES        2

// Initialize full step rotary encoder with internal pull-up pins enabled
// and default sensitivity=100
RotaryFullStep rotaries[NUM_ROTARIES] = {
    RotaryFullStep(ROTARY1_PIN1, ROTARY1_PIN2),
    RotaryFullStep(ROTARY2_PIN1, ROTARY2_PIN2)
};

// Global variables
int pinStateLast[NUM_ROTARIES];

// Forward declarations
void handleRotaryButton(uint8_t rotaryId);

void setup()
{
  // Initialize Serial port
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial.println(F("\nExample multiple polled full step Rotary Encoders"));
  Serial.println(F("Press the rotary button to change sensitivity"));

  // Enable internal pull-up for the rotary button pins
  pinMode(ROTARY1_BUTTON_PIN, INPUT_PULLUP);
  pinMode(ROTARY2_BUTTON_PIN, INPUT_PULLUP);
}

void loop()
{
  // Handle multiple Rotary Encoders
  for (uint8_t i = 0; i < NUM_ROTARIES; i++) {
    // Handle rotary button
    handleRotaryButton(i);

    // Read rotary state
    int rotaryState = rotaries[i].read();

    // Print count value when rotary changed
    if ((rotaryState > 0) || (rotaryState < 0)) {
      Serial.print(F("Rotary "));
      Serial.print(i + 1);
      Serial.print(F(": "));
      Serial.println(rotaryState);
    }
  }
}

void handleRotaryButton(uint8_t rotaryId)
{
  int pinState;

  // Read Rotary button state
  switch (rotaryId) {
    case 0:
      pinState = digitalRead(ROTARY1_BUTTON_PIN);
      break;
    case 1:
      pinState = digitalRead(ROTARY2_BUTTON_PIN);
      break;
    default:
      return;
  }

  // Check if Rotary button state changed
  if (pinStateLast[rotaryId] != pinState) {
    pinStateLast[rotaryId] = pinState;

    // Check if button is down
    if (pinState == 0) {
      uint8_t sensitivity;

      // Get current Rotary sensitivity
      sensitivity = rotaries[rotaryId].getSensitivity();

      // Increment sensitivity value in steps of 50
      if (sensitivity >= 250) {
        sensitivity = 0;
      } else {
        sensitivity += 50;
      }

      // Print new sensitivity value on Serial
      Serial.print(F("Rotary "));
      Serial.print(rotaryId + 1);
      Serial.print(F(" sensitivity: "));
      Serial.println(sensitivity);

      // Set new Rotary sensitivity value
      rotaries[rotaryId].setSensitivity(sensitivity);
    }
  }
}
