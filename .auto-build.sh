#!/bin/sh

################################################################################
# Title         : .auto-build.sh
# Date created  : 2 August 2018
__AUTHOR__="Erriez"
#
# This script will start PlatformIO build.
#
################################################################################

################################################################################
##### Setup this script and get the current gh-pages branch.               #####
echo 'Setting up the script...'

# Exit with nonzero exit code if anything fails
set -e

# Build sources
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/Interrupt/InterruptFullStepBasic/InterruptFullStepBasic.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/Interrupt/InterruptFullStepButton/InterruptFullStepButton.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/Interrupt/InterruptFullStepCounter/InterruptFullStepCounter.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/Polled/PolledFullStepBasic/PolledFullStepBasic.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/Polled/PolledFullStepButton/PolledFullStepButton.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/Polled/PolledFullStepCounter/PolledFullStepCounter.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/Polled/PolledFullStepMultiple/PolledFullStepMultiple.ino
