cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)

#-------------------------------------------------------------------------------
# User configuration
#-------------------------------------------------------------------------------
# Project name
set(PROJECT_NAME    ArduinoLibraryRotary)

# Library directory
set(LIBRARY_DIR     C:/Users/User/Documents/Arduino/libraries)

# Configure board, default Arduino UNO
set(BOARD           uno)

# Configure sketch
set(SKETCH examples/Polled/FullStepBasic/FullStepBasic.ino)

# Configure serial port, such as:
#     Windows: COM1
#     Linux:   /dev/ttyUSB0
set(SERIAL_PORT     COM1)

#-------------------------------------------------------------------------------
# Project configuation
#-------------------------------------------------------------------------------
# Configure project
project(${PROJECT_NAME})

set(ROTARY_LIBRARY_DIR    ${LIBRARY_DIR}/ArduinoLibraryRotary/src)

include_directories(${ROTARY_LIBRARY_DIR})

generate_arduino_library(
        RotaryLib
        SRCS
            ${ROTARY_LIBRARY_DIR}/Rotary.cpp
        HDRS
            ${ROTARY_LIBRARY_DIR}/Rotary.h
)

set(${CMAKE_PROJECT_NAME}_SKETCH    ${SKETCH})
set(${CMAKE_PROJECT_NAME}_LIBS      RotaryLib)
set(${CMAKE_PROJECT_NAME}_BOARD     ${BOARD})
set(${CMAKE_PROJECT_NAME}_PORT      ${SERIAL_PORT})

generate_arduino_firmware(${CMAKE_PROJECT_NAME})
