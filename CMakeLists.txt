cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_TOOLCHAIN_FILE external/arduino-cmake/cmake/ArduinoToolchain.cmake)

project(arduino_pong
  LANGUAGES C CXX
  VERSION 0.1.0)

#print_board_list()
#print_programmer_list()

set(arduino_pong_SOURCES src/main.cpp)

generate_arduino_firmware(${PROJECT_NAME}
    SRCS ${arduino_pong_SOURCES}
    BOARD uno
    PORT /dev/ttyACM0
    SERIAL picocom @SERIAL_PORT@ -b 9600 -l
    )
