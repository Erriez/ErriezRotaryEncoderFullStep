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

/*!
 * \file ErriezRotaryFullStep.cpp
 * \brief Three speed full step Rotary Encoder library for Arduino.
 * \details
 *      Source:         https://github.com/Erriez/ErriezRotaryEncoderFullStep
 *      Documentation:  https://erriez.github.io/ErriezRotaryEncoderFullStep
 */

#if (defined(__AVR__) || defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_STM32F1))
#include <avr/pgmspace.h>
#else
#include <pgmspace.h>
#endif

#include "ErriezRotaryFullStep.h"

#define DIR_NONE  0x00      //!< No complete step yet
#define DIR_CW    0x10      //!< Clockwise step
#define DIR_CCW   0x20      //!< Counter-clockwise step

// Use the full-step state table, clockwise and counter clockwise
// Emits a code at '00' only
#define RFS_START          0x00     //!< Rotary full step start
#define RFS_CW_FINAL       0x01     //!< Rotary full step clock wise final
#define RFS_CW_BEGIN       0x02     //!< Rotary full step clock begin
#define RFS_CW_NEXT        0x03     //!< Rotary full step clock next
#define RFS_CCW_BEGIN      0x04     //!< Rotary full step counter clockwise begin
#define RFS_CCW_FINAL      0x05     //!< Rotary full step counter clockwise final
#define RFS_CCW_NEXT       0x06     //!< Rotary full step counter clockwise next

static const PROGMEM uint8_t fullStepTable[7][4] = {
    // RFS_START
    {RFS_START,      RFS_CW_BEGIN,  RFS_CCW_BEGIN, RFS_START},
    // RFS_CW_FINAL
    {RFS_CW_NEXT,    RFS_START,     RFS_CW_FINAL,  RFS_START | DIR_CW},
    // RFS_CW_BEGIN
    {RFS_CW_NEXT,    RFS_CW_BEGIN,  RFS_START,     RFS_START},
    // RFS_CW_NEXT
    {RFS_CW_NEXT,    RFS_CW_BEGIN,  RFS_CW_FINAL,  RFS_START},
    // RFS_CCW_BEGIN
    {RFS_CCW_NEXT,   RFS_START,     RFS_CCW_BEGIN, RFS_START},
    // RFS_CCW_FINAL
    {RFS_CCW_NEXT,   RFS_CCW_FINAL, RFS_START,     RFS_START | DIR_CCW},
    // RFS_CCW_NEXT
    {RFS_CCW_NEXT,   RFS_CCW_FINAL, RFS_CCW_BEGIN, RFS_START},
};

/*!
 * \brief
 *     Constructor full step Rotary Encoder
 * \param pin1
 *     Rotary Encoder pin 1
 * \param pin2
 *     Rotary Encoder pin 2
 * \param pullUp
 *     true:  Enable internal pull-up on Rotary Encoder pins [default argument].
 *     false: Disable internal pull-up on Rotary Encoder pins.
 * \param sensitivity
 *     Set sensitivity rotation speed value 0..255.
 *     A higher is more sensitive for rotation speed, a smaller value is less
 *     sensitive or will disable speed detection.
 *     Default is 100.
 */
RotaryFullStep::RotaryFullStep(uint8_t pin1, uint8_t pin2, bool pullUp, uint8_t sensitivity) :
    _pin1(pin1), _pin2(pin2), _state(0), _sensitivity(sensitivity)
{
    if (pullUp) {
        // Enable internal pull-up
        pinMode(_pin1, INPUT_PULLUP);
        pinMode(_pin2, INPUT_PULLUP);
    }
}

/*!
 * \brief
 *     Read Rotary Encoder state
 * \details
 *     Call this function as fast as possible to prevent missing pin changes.
 *     This seems to work for most rotary encoders when calling this function
 *     within 10ms in an endless loop.
 *
 *     The sensitivity value is used to calculate three rotation speeds by
 *     measuring the speed of the Rotary Encoder pin changes. The rotation speed
 *     depends on the number of Rotary notches and knob size. The value should
 *     experimentally determined.
 * \return Rotary speed and direction
 *     -3: Counter clockwise turn, multiple notches fast
 *     -2: Counter clockwise turn, multiple notches
 *     -1: Counter clockwise turn, single notch
 *      0:  No change
 *      1:  Clockwise turn, single notch
 *      2:  Clockwise turn, multiple notches
 *      3:  Clockwise turn, multiple notches fast
 */
int RotaryFullStep::read()
{
    int pinState;
    int rotaryState;
    unsigned long timeStamp;
    unsigned long changeTime;

    // Sample rotary digital pins
    pinState = (digitalRead(_pin1) << 1) | digitalRead(_pin2);

    // Determine new state from the pins and state table.
    _state = pgm_read_byte(&fullStepTable[_state & 0x0f][pinState]);

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
        timeStamp = millis();
        changeTime = timeStamp - _lastChange;
        _lastChange = timeStamp;

        // Check speed change
        if (changeTime < (_sensitivity / 2)) {
            rotaryState *= 3;
        } else if (changeTime < _sensitivity) {
            rotaryState *= 2;
        }
    }

    return rotaryState;
}

/*!
 * \brief
 *     Set sensitivity value.
 * \param sensitivity
 *     Sensitivity value 0..255
 */
void RotaryFullStep::setSensitivity(uint8_t sensitivity)
{
    _sensitivity = sensitivity;
}

/*!
 * \brief
 *     Get sensitivity value.
 * \return
 *     Sensitivity value 0..255.
 */
uint8_t RotaryFullStep::getSensitivity()
{
    return _sensitivity;
}
