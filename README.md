# 3 speed Rotary library for Arduino

This is a three speed rotary library for Arduino. Half and full step rotaries 
are supported.

## Hardware
Connect the two rotary pins to the digital pins of an Arduino board.

A third rotary button pin is not used in the Rotary library.

### Rotary - Arduino UNO example
![alt text](https://github.com/Erriez/ArduinoLibraryRotary/extras/FrtizingRotary.png "3-pin Rotary Arduino connection")


## Examples
The following examples are available:
* Rotary | FullStep
* Rotary | HalfStep
* Rotary | Button

Half or full speed depends on the slip contacts inside the rotary. Try the Full 
step example first, followed by the half step rotary to see the differences.

## Installation
1. Start the Arduino IDE.
2. Download the latest version from:  
   https://github.com/Erriez/ArduinoLibraryRotary/archive/master.zip
3. Click Sketch | Include Library | Add .ZIP Library... and select this ZIP.
5. Run the example.

## Usage

**Initialization**
```c++
#include <Rotary.h>
  
// Configure rotary pins connected to your Arduino board
#define ROTARY_PIN1   2
#define ROTARY_PIN2   3
  
// Initialize full step rotary
Rotary rotary(ROTARY_PIN1, ROTARY_PIN2, FullStep);
  
// Or initialize half step rotary
Rotary rotary(ROTARY_PIN1, ROTARY_PIN2, HalfStep);
```

**Read rotary**
```c++
void loop()
{
    int rotaryState = rotary.read();
  
    // rotaryState = -3: Turn left fast
    // rotaryState = -2: Turn left faster
    // rotaryState = -1: Turn left
    // rotaryState = 0:  No change
    // rotaryState = 1:  Turn right
    // rotaryState = 2:  Turn right faster
    // rotaryState = 3:  Turn right fast
}
```
