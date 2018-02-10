# 3 speed Rotary Encoder library for Arduino

This is an optimized three speed rotary encoder library for Arduino. Half and full step rotary encoder types 
are supported by using polling or interrupts.

## Hardware
Connect the two rotary pins to the digital pins of an Arduino board.

A third rotary button pin is not used in the Rotary library.

### Interrupts

Both rotary pins must be connected to a DIGITAL pin with interrupt support, such as `INT0` or `INT1`. This is chip specific. Please refer to the documentation of your board or [attachInterrupt()](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/).

### Rotary - Arduino UNO example

The connection below can be used for polled and interrupts. An optional button can be connected to DIGITAL pin 4.

![alt text](https://raw.githubusercontent.com/Erriez/ArduinoLibraryRotary/master/extras/FritzingRotary.png "3-pin Rotary Encoder Arduino connection")


## Examples
The following examples are available:
* Rotary | Interrupt | [FullStepInterrupt](https://github.com/Erriez/ArduinoLibraryRotary/blob/master/examples/Interrupt/FullStepInterrupt/FullStepInterrupt.ino)
* Rotary | Interrupt | [HalfStepInterrupt](https://github.com/Erriez/ArduinoLibraryRotary/blob/master/examples/Interrupt/HalfStepInterrupt/HalfStepInterrupt.ino)
* Rotary | Polled | [FullStepBasic](https://github.com/Erriez/ArduinoLibraryRotary/blob/master/examples/Polled/FullStepBasic/FullStepBasic.ino)
* Rotary | Polled | [FullStepButton](https://github.com/Erriez/ArduinoLibraryRotary/blob/master/examples/Polled/FullStepBasic/FullStepBasic.ino) (Requires an additional IO pin from the button on the Rotary Encoder)
* Rotary | Polled | [FullStepCounter](https://github.com/Erriez/ArduinoLibraryRotary/blob/master/examples/Polled/FullStepCounter/FullStepCounter.ino)
* Rotary | Polled | [HalfStepBasic](https://github.com/Erriez/ArduinoLibraryRotary/blob/master/examples/Polled/HalfStepBasic/HalfStepBasic.ino)
* Rotary | Polled | [HalfStepButton](https://github.com/Erriez/ArduinoLibraryRotary/blob/master/examples/Polled/HalfStepBasic/HalfStepBasic.ino)  (Requires an additional IO pin from the button on the Rotary Encoder)
* Rotary | Polled | [HalfStepCounter](https://github.com/Erriez/ArduinoLibraryRotary/blob/master/examples/Polled/HalfStepCounter/HalfStepCounter.ino)

Half or full speed depends on the slip contacts inside the rotary. Try the Full step example first, followed by the half step rotary to see the differences.

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

**Read rotary with polling**
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

**Read rotary with interrupts**

```c++
#include <Rotary.h>

// Connect rotary to Arduino DIGITAL pins with interrupt support:
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

// Initialize full step rotary
Rotary rotary(ROTARY_PIN1, ROTARY_PIN2, FullStep);

void setup()
{
  // Initialize pin change interrupt on both rotary encoder pins
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN1), rotaryInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN2), rotaryInterrupt, CHANGE);
}

void rotaryInterrupt()
{
  int rotaryState;

  // Read rotary state
  rotaryState = rotary.read();
    
  if (rotaryState > 0) {
    // Rotary right, speed 1, 2 or 3
  } else if (rotaryState < 0) {
    // Rotary left, speed -1, -2 or -3
  }
}
```

## Installation with Git

### Install Git client for Windows

Install a [Git client for Windows](https://git-scm.com/download/win).

### Install Git client for Linux

Open a command prompt and install a Git client for Linux, such as Debian Ubuntu:

```shell
sudo apt-get install git
```

### Windows and Linux

The library must be installed in the Sketchbook directory which is configured in the Preferences dialog box.

1. Click `File` | `Preferences` |`Settings` tab and copy the Sketchbook location.
   The path on Windows is something like: `C:\Users\User\Documents\Arduino`
   The path on Linux is something like: `/home/user/Arduino`
2. Open a command prompt and type: 

```shell
# Run on Windows:
cd C:\Users\User\Documents\Arduino
# Or run on Linux:
cd /home/user/Arduino

# Run the git clone library once:
git clone git clone https://github.com/Erriez/ArduinoLibraryRotary.git

# Update the library:
git pull
```

3. Restart the Arduino IDE.