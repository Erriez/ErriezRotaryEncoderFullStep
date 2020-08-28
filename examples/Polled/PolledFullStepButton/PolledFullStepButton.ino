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

/* Button example polled full step Rotary Encoder
 * Source:         https://github.com/Erriez/ErriezRotaryEncoderFullStep
 * Documentation:  https://erriez.github.io/ErriezRotaryEncoderFullStep
 */

#include <ErriezRotaryFullStep.h>

// Connect rotary pins to the DIGITAL or ANALOG pins of the Arduino board
// Use A0..A7 when using analog pins
#define ROTARY_PIN1         2
#define ROTARY_PIN2         3
#define ROTARY_BUTTON_PIN   4

// Initialize full step rotary encoder with internal pull-up pins enabled
// and default sensitivity=100
RotaryFullStep rotary(ROTARY_PIN1, ROTARY_PIN2);

// Or initialize full step rotary encoder with internal pull-up pins disabled
// and default sensitivity=100
// RotaryFullStep rotary(ROTARY_PIN1, ROTARY_PIN2, false);

// Or initialize full step rotary encoder with internal pull-up pins enabled and
// sensitivity value 1..255
// A higher value is more sensitive
// RotaryFullStep rotary(ROTARY_PIN1, ROTARY_PIN2, true, 200);

// Global variables
int count = 0;
int countLast = 0;


void setup()
{
    // Initialize Serial port
    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    Serial.println(F("\nButton example polled full step Rotary Encoder"));

    // Enable internal pull-up for the rotary button pin
    pinMode(ROTARY_BUTTON_PIN, INPUT_PULLUP);
}

void loop()
{
    int rotaryState;

    if (digitalRead(ROTARY_BUTTON_PIN) == 0) {
        // Reset count when rotary button is down
        count = 0;
    } else {
        // Read rotary state (Counter clockwise) -2, -1, 0, 1, 2 (Clockwise)
        rotaryState = rotary.read();

        // Count up or down by using rotary speed
        if (rotaryState == 0) {
            // No change
            return;
        } else if (abs(rotaryState) >= 2) {
            count += rotaryState * 2;
        } else {
            count += rotaryState;
        }

        // Limit count to a minimum and maximum value
        if (count > 100) {
            count = 100;
        }
        if (count < 0) {
            count = 0;
        }
    }

    // Print count value when count value changed
    if (countLast != count) {
        countLast = count;
        Serial.print(F("Count: "));
        Serial.println(count);
    }
}
