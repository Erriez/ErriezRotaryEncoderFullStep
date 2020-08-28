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

/* Basic example full step Rotary Encoder with interrupts
 * Source:         https://github.com/Erriez/ErriezRotaryEncoderFullStep
 * Documentation:  https://erriez.github.io/ErriezRotaryEncoderFullStep
 */

#include <ErriezRotaryFullStep.h>

// Connect rotary pins to the DIGITAL pins of the Arduino board with interrupt
// support:
//
// +-----------------------------------+----------------------------+
// |              Board                |    DIGITAL interrupt pins  |
// +-----------------------------------+----------------------------+
// | Uno, Nano, Mini, other 328-based  |  2, 3                      |
// | Mega, Mega2560, MegaADK           |  2, 3, 18, 19, 20, 21      |
// | Micro, Leonardo, other 32u4-based |  0, 1, 2, 3, 7             |
// | WeMos D1 R2 & mini (ESP8266)      |  12 = D6; 13 = D7; 14 = D5 |
// +-----------------------------------+----------------------------+
//
#define ROTARY_PIN1   2
#define ROTARY_PIN2   3

// Initialize full step rotary encoder with internal pull-up pins enabled
// and default sensitivity=100
RotaryFullStep rotary(ROTARY_PIN1, ROTARY_PIN2);

// Forward declaration
void rotaryInterrupt();

void setup()
{
  // Initialize Serial port
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial.println(F("\nBasic example full step Rotary Encoder with interrupts"));

  // Initialize pin change interrupt on both rotary encoder pins
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN1), rotaryInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN2), rotaryInterrupt, CHANGE);
}

void loop()
{
  // Wait for interrupt
}

#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
ICACHE_RAM_ATTR
#endif
void rotaryInterrupt()
{
  int rotaryState;

  // Read rotary state
  rotaryState = rotary.read();

  // Print count value when count value changed
  if ((rotaryState > 0) || (rotaryState < 0)) {
    Serial.println(rotaryState);
  }
}
