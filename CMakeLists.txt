cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ARDUINO_PONG_BUILD_ARDUINO "Build for Arduino" ON)

if(ARDUINO_PONG_BUILD_ARDUINO)
  set(CMAKE_TOOLCHAIN_FILE external/arduino-cmake/cmake/ArduinoToolchain.cmake)
endif()

project(arduino_pong
  LANGUAGES C CXX
  VERSION 0.1.0)

#print_board_list()
#print_programmer_list()

set(arduino_pong_HEADERS
  src/Rectangle.hpp
  src/Ball.hpp
  src/Paddle.hpp)
set(arduino_pong_SOURCES
  src/Rectangle.cpp
  src/Ball.cpp
  src/Paddle.cpp)
set(arduino_pong_MAIN src/main.cpp)

if(ARDUINO_PONG_BUILD_ARDUINO)
  generate_arduino_firmware(${PROJECT_NAME}
    SRCS ${arduino_pong_SOURCES} ${arduino_pong_MAIN}
    BOARD uno
    PORT /dev/ttyACM0
    SERIAL picocom @SERIAL_PORT@ -b 9600 -l)
else()
  add_library(${PROJECT_NAME} STATIC ${arduino_pong_SOURCES} ${arduino_pong_HEADERS})
  target_include_directories(${PROJECT_NAME} INTERFACE src)
  # Disable exceptions like in avr-gcc
  target_compile_options(${PROJECT_NAME} PRIVATE -fno-exceptions)
endif()

# Setup include-what-you-use and clang-tidy for additional checks
set_target_properties(${PROJECT_NAME}
  PROPERTIES
  CXX_INCLUDE_WHAT_YOU_USE "include-what-you-use"
  CXX_CLANG_TIDY "clang-tidy")

# Compile features
target_compile_options(${PROJECT_NAME} PUBLIC -std=gnu++14)

# disable rtti
target_compile_options(${PROJECT_NAME} PRIVATE -fno-rtti)

if(NOT ARDUINO_PONG_BUILD_ARDUINO)
  enable_testing()
  add_subdirectory(test)
endif()
