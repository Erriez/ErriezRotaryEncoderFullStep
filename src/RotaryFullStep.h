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

/*!
 * \file RotaryFullStep.h
 * \brief Three speed full step Rotary Encoder library for Arduino
 * \details
 *      Source:         https://github.com/Erriez/ErriezRotaryEncoderFullStep
 *      Documentation:  https://erriez.github.io/ErriezRotaryEncoderFullStep
 */

#ifndef ROTARY_FULL_STEP_H__
#define ROTARY_FULL_STEP_H__

#include <Arduino.h>

/*!
 * \brief Full step Rotary Encoder class
 */
class RotaryFullStep
{
public:
    RotaryFullStep(uint8_t pin1, uint8_t pin2, bool pullUp=true, uint8_t sensitivity=100);
    int read();
    void setSensitivity(uint8_t sensitivity);
    uint8_t getSensitivity();

private:
    unsigned long  _lastChange;
    uint8_t _pin1;
    uint8_t _pin2;
    uint8_t _state;
    uint8_t _sensitivity;
};

#endif // ROTARY_FULL_STEP_H__
