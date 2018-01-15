/*
 * MIT License
 *
 * Copyright (c) 2018 Erriez
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

#include <avr/pgmspace.h>
#include "Rotary.h"

// No complete step yet
#define DIR_NONE  0x00
// Clockwise step
#define DIR_CW    0x10
// Counter-clockwise step
#define DIR_CCW   0x20

// Use the half-step state table (emits a code at 00 and 11)
#define RHS_START         0x00
#define RHS_CCW_BEGIN     0x01
#define RHS_CW_BEGIN      0x02
#define RHS_START_M       0x03
#define RHS_CW_BEGIN_M    0x04
#define RHS_CCW_BEGIN_M   0x05

static const PROGMEM uint8_t halfStepTable[6][4] = {
  // RHS_START (00)
  {RHS_START_M,           RHS_CW_BEGIN,     RHS_CCW_BEGIN,    RHS_START},
  // RHS_CCW_BEGIN
  {RHS_START_M | DIR_CCW, RHS_START,        RHS_CCW_BEGIN,    RHS_START},
  // RHS_CW_BEGIN
  {RHS_START_M | DIR_CW,  RHS_CW_BEGIN,     RHS_START,        RHS_START},
  // RHS_START_M (11)
  {RHS_START_M,           RHS_CCW_BEGIN_M,  RHS_CW_BEGIN_M,   RHS_START},
  // RHS_CW_BEGIN_M
  {RHS_START_M,           RHS_START_M,      RHS_CW_BEGIN_M,   RHS_START | DIR_CW},
  // RHS_CCW_BEGIN_M
  {RHS_START_M,           RHS_CCW_BEGIN_M,  RHS_START_M,      RHS_START | DIR_CCW},
};

// Use the full-step state table (emits a code at 00 only)
#define RF_START          0x00
#define RF_CW_FINAL       0x01
#define RF_CW_BEGIN       0x02
#define RF_CW_NEXT        0x03
#define RF_CCW_BEGIN      0x04
#define RF_CCW_FINAL      0x05
#define RF_CCW_NEXT       0x06

static const PROGMEM uint8_t fullStepTable[7][4] = {
  // RF_START
  {RF_START,      RF_CW_BEGIN,  RF_CCW_BEGIN, RF_START},
  // RF_CW_FINAL
  {RF_CW_NEXT,    RF_START,     RF_CW_FINAL,  RF_START | DIR_CW},
  // RF_CW_BEGIN
  {RF_CW_NEXT,    RF_CW_BEGIN,  RF_START,     RF_START},
  // RF_CW_NEXT
  {RF_CW_NEXT,    RF_CW_BEGIN,  RF_CW_FINAL,  RF_START},
  // RF_CCW_BEGIN
  {RF_CCW_NEXT,   RF_START,     RF_CCW_BEGIN, RF_START},
  // RF_CCW_FINAL
  {RF_CCW_NEXT,   RF_CCW_FINAL, RF_START,     RF_START | DIR_CCW},
  // RF_CCW_NEXT
  {RF_CCW_NEXT,   RF_CCW_FINAL, RF_CCW_BEGIN, RF_START},
};

Rotary::Rotary(uint8_t pin1, uint8_t pin2, RotaryStepType halfStep,
               bool pullUp) :
  _pin1(pin1),
  _pin2(pin2),
  _halfStep(halfStep),
  _state(0)
{
  if (pullUp) {
    // Enable internal pull-up
    pinMode(_pin1, INPUT_PULLUP);
    pinMode(_pin2, INPUT_PULLUP);
  }
}

int Rotary::read()
{
  int pinState;
  int rotaryState;

  // Sample rotary digital pins
  pinState = (digitalRead(_pin1) << 1) | digitalRead(_pin2);

  // Determine new state from the pins and state table.
  if (_halfStep == HalfStep) {
    _state = pgm_read_byte(&halfStepTable[_state & 0x0f][pinState]);
  } else {
    _state = pgm_read_byte(&fullStepTable[_state & 0x0f][pinState]);
  }

  // Check rotary state
  switch (_state & 0x30) {
    case DIR_CW:
      rotaryState = 1;
      break;
    case DIR_CCW:
      rotaryState = -1;
      break;
    case DIR_NONE:
    default:
      rotaryState = 0;
  }

  // Check if rotary changed
  if (rotaryState != 0) {
    // Check speed change
    if ((millis() - _lastChange) < 50) {
      rotaryState *= 3;
    } else if ((millis() - _lastChange) < 100) {
      rotaryState *= 2;
    }
    _lastChange = millis();
  }

  return rotaryState;
}
