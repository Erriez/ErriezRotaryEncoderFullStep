#!/bin/sh

# Install Python platformio 
# pip install -U platformio

# Update library
# git fetch
# git pull

# Build example(s)
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Interrupt/InterruptFullStepBasic/InterruptFullStepBasic.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Interrupt/InterruptFullStepButton/InterruptFullStepButton.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Interrupt/InterruptFullStepCounter/InterruptFullStepCounter.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Polled/PolledFullStepBasic/PolledFullStepBasic.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Polled/PolledFullStepButton/PolledFullStepButton.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Polled/PolledFullStepCounter/PolledFullStepCounter.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Polled/PolledFullStepMultiple/PolledFullStepMultiple.ino
