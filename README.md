# 3 speed Rotary Encoder Full Step library for Arduino
[![Build Status](https://travis-ci.org/Erriez/ErriezRotaryEncoderFullStep.svg?branch=master)](https://travis-ci.org/Erriez/ErriezRotaryEncoderFullStep)

This is an optimized three speed Rotary Encoder library for Arduino which supports:

* Full step Rotary Encoder types.
* Detect three rotation speeds.
* Configurable rotation speed sensitivity.
* Polling and interrupt based.
* Single or multiple Rotary Encoders.
* Optional Rotary button.
* Pin state table in flash.

![Rotary encoder](https://raw.githubusercontent.com/Erriez/ErriezRotaryEncoderFullStep/master/extras/RotaryEncoder.png)


## Full step / half step Rotary Encoders

The difference between a full step or half step Rotary Encoder type is how the data signals of the two pins are generated. It depends on the mechanical construction of the notches and contacts inside the Rotary Encoder.

Please refer to the [ErriezRotaryEncoderHalfStep](https://github.com/Erriez/ErriezRotaryEncoderHalfStep) library for half step Rotary Encoders. 
Experiment with the half step and full step libraries which works optimal for your Rotary Encoder.


## Hardware

Connect the two rotary pins to the DIGITAL pins of an Arduino board.

A third rotary button pin is not used in the Rotary library, but can be used in the sketch.

Tested with Arduino IDE v1.8.5 on hardware:

* Arduino UNO
* Arduino Nano
* Arduino Micro
* Arduino Pro or Pro Mini
* Arduino Mega or Mega2560
* Arduino Leonardo
* WeMos D1 R2 & mini (ESP8266)


### Interrupts

Both rotary pins must be connected to a DIGITAL pin with interrupt support, such as `INT0` or `INT1`. This is chip specific. Please refer to the documentation of your board or [attachInterrupt()](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/).


### Arduino UNO hardware

The connection below can be used for polled and interrupts. An optional button pin can be connected to DIGITAL pin 4.

![alt text](https://raw.githubusercontent.com/Erriez/ErriezRotaryEncoderFullStep/master/extras/FritzingRotary.png"3-pin Rotary Encoder Arduino connection")

|    Rotary pin     | Arduino UNO/NANO/Mega2560/Leonardo board |
| :---------------: | :--------------------------------------: |
|         1         |           DIGITAL pin 2 (INT0)           |
|         2         |           DIGITAL pin 3 (INT1)           |
| Button (optional) |              DIGITAL pin 4               |
|        GND        |                   GND                    |



### Arduino WeMos D1 R2 & mini (ESP8266) hardware

Note that some ESP8266 pins mixes ESP8622 GPIO pins with Arduino digital pins. Connect a Rotary Encoder to the following pins which can be used with polled and interrupt examples:

|    Rotary pin     | ESP8622 pin | Text on board / WeMos D1 & R2 |
| :---------------: | :---------: | :---------------------------: |
|         1         |   GPIO13    |           D7 (MOSI)           |
|         2         |   GPIO12    |           D6 (MISO)           |
| Button (optional) |   GPIO14    |           D5 (SCK)            |
|  LED (Not used)   |    GPIO2    |              D4               |
|        GND        |     GND     |              GND              |

**Note:** An external pull-up resistor is required when a pin does not have an internal pull-up.

```c++
// Connect the rotary pins to the WeMos D1 R2 board:
#define ROTARY_PIN1         12
#define ROTARY_PIN2         13
#define ROTARY_BUTTON_PIN   14
```



## Examples

The following examples are available:
* Rotary | Interrupt | [InterruptFullStepBasic](https://github.com/Erriez/ErriezRotary/blob/master/examples/Interrupt/InterruptFullStepBasic/InterruptFullStepBasic.ino)
* Rotary | Interrupt | [InterruptFullStepButton](https://github.com/Erriez/ErriezRotary/blob/master/examples/Interrupt/InterruptFullStepButton/InterruptFullStepButton.ino)
* Rotary | Interrupt | [InterruptFullStepCounter](https://github.com/Erriez/ErriezRotary/blob/master/examples/Interrupt/InterruptFullStepCounter/InterruptFullStepCounter.ino)
* Rotary | Polled | [PolledFullStepBasic](https://github.com/Erriez/ErriezRotary/blob/master/examples/Polled/PolledFullStepBasic/PolledFullStepBasic.ino)
* Rotary | Polled | [PolledFullStepButton](https://github.com/Erriez/ErriezRotary/blob/master/examples/Polled/PolledFullStepButton/PolledFullStepButton.ino)
* Rotary | Polled | [PolledFullStepCounter](https://github.com/Erriez/ErriezRotary/blob/master/examples/Polled/PolledFullStepCounter/PolledFullStepCounter.ino)
* Rotary | Polled | [PolledFullStepMultiple](https://github.com/Erriez/ErriezRotary/blob/master/examples/Polled/PolledFullStepMultiple/PolledFullStepMultiple.ino)


## Documentation

- [Doxygen online HTML](https://Erriez.github.io/ErriezRotaryEncoderFullStep)
- [Doxygen PDF](https://github.com/Erriez/ErriezRotaryEncoderFullStep/raw/gh-pages/latex/ErriezRotaryEncoderFullStep.pdf)


## Usage

**Read rotary with polling**
```c++
#include <ErriezRotaryFullStep.h>

// Connect rotary pins to the DIGITAL pins of the Arduino board
#define ROTARY_PIN1   2
#define ROTARY_PIN2   3
  
// Enable ONE of the three constructors below with different number of arguments:

// Initialize full step rotary encoder, default pull-up enabled, default 
// sensitive=100
RotaryFullStep rotary(ROTARY_PIN1, ROTARY_PIN2);

// Or initialize full step rotary encoder, pull-up disabled, default sensitive=100
// RotaryFullStep rotary(ROTARY_PIN1, ROTARY_PIN2, false);

// Or initialize full step rotary encoder, pull-up enabled, sensitive 1..255
// A higher value is more sensitive
// RotaryFullStep rotary(ROTARY_PIN1, ROTARY_PIN2, true, 150);

void loop()
{
  int rotaryState = rotary.read();
  
  // rotaryState = -3: Counter clockwise turn, multiple notches fast
  // rotaryState = -2: Counter clockwise turn, multiple notches
  // rotaryState = -1: Counter clockwise turn, single notch
  // rotaryState = 0:  No change
  // rotaryState = 1:  Clockwise turn, single notch
  // rotaryState = 2:  Clockwise turn, multiple notches
  // rotaryState = 3:  Clockwise turn, multiple notches fast
}
```

**Read rotary with interrupts**

```c++
#include <ErriezRotaryFullStep.h>

// Connect rotary pins to Arduino DIGITAL pins with interrupt support:
//
// +-----------------------------------+--------------------------+
// |              Board                |  DIGITAL interrupt pins  |
// +-----------------------------------+--------------------------+
// | Uno, Nano, Mini, other 328-based  |  2, 3                    |
// | Mega, Mega2560, MegaADK           |  2, 3, 18, 19, 20, 21    |
// | Micro, Leonardo, other 32u4-based |  0, 1, 2, 3, 7           |
// +-----------------------------------+--------------------------+
//
#define ROTARY_PIN1   2
#define ROTARY_PIN2   3

// Enable ONE of the three constructors below with different number of arguments:

// Initialize full step rotary encoder, default pull-up enabled, default 
// sensitive=100
RotaryFullStep rotary(ROTARY_PIN1, ROTARY_PIN2);

// Or initialize full step rotary encoder, pull-up disabled, default sensitive=100
// RotaryFullStep rotary(ROTARY_PIN1, ROTARY_PIN2, false);

// Or initialize full step rotary encoder, pull-up enabled, sensitive 1..255
// A higher value is more sensitive
// RotaryFullStep rotary(ROTARY_PIN1, ROTARY_PIN2, true, 150);

void setup()
{
  // Initialize pin change interrupt on both rotary encoder pins
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN1), rotaryInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN2), rotaryInterrupt, CHANGE);
}

void rotaryInterrupt()
{
  int rotaryState = rotary.read();
  
  // rotaryState = -3: Counter clockwise turn, multiple notches fast
  // rotaryState = -2: Counter clockwise turn, multiple notches
  // rotaryState = -1: Counter clockwise turn, single notch
  // rotaryState = 0:  No change
  // rotaryState = 1:  Clockwise turn, single notch
  // rotaryState = 2:  Clockwise turn, multiple notches
  // rotaryState = 3:  Clockwise turn, multiple notches fast
}
```


## Library dependencies

- None.


## Library installation

Please refer to the [Wiki](https://github.com/Erriez/ErriezArduinoLibrariesAndSketches/wiki) page.


## Other Arduino Libraries and Sketches from Erriez

* [Erriez Libraries and Sketches](https://github.com/Erriez/ErriezArduinoLibrariesAndSketches)
