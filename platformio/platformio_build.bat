rem Install Python27 platformio
rem C:\Python27\Scripts\pip.exe install -U platformio

rem Set Python path
set PATH=%PATH%;C:\Python27
set PATH=%PATH%;C:\Python27\Scripts

rem Update library
rem git fetch
rem git pull

rem Build example(s)
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Interrupt/InterruptFullStepBasic/InterruptFullStepBasic.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Interrupt/InterruptFullStepButton/InterruptFullStepButton.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Interrupt/InterruptFullStepCounter/InterruptFullStepCounter.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Polled/PolledFullStepBasic/PolledFullStepBasic.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Polled/PolledFullStepButton/PolledFullStepButton.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Polled/PolledFullStepCounter/PolledFullStepCounter.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Polled/PolledFullStepMultiple/PolledFullStepMultiple.ino

@pause