cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(ARDUINO_PONG_BUILD_ARDUINO)
  set(CMAKE_TOOLCHAIN_FILE external/arduino-cmake/cmake/ArduinoToolchain.cmake)
endif()

project(arduino_pong
  LANGUAGES C CXX
  VERSION 0.1.0)

#print_board_list()
#print_programmer_list()

set(arduino_pong_SOURCES)
set(arduino_pong_MAIN src/main.cpp)
set(arduino_pong_HEADERS)

if(ARDUINO_PONG_BUILD_ARDUINO)
  generate_arduino_firmware(${PROJECT_NAME}
    SRCS ${arduino_pong_SOURCES} ${arduino_pong_MAIN}
    BOARD uno
    PORT /dev/ttyACM0
    SERIAL picocom @SERIAL_PORT@ -b 9600 -l)
else()
  add_library(${PROJECT_NAME} STATIC ${arduino_pong_SOURCES} ${arduino_pong_HEADERS})
endif()

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  CXX_INCLUDE_WHAT_YOU_USE "include-what-you-use"
  CXX_CLANG_TIDY "clang-tidy")

# disable rtti
target_compile_options(${PROJECT_NAME} PRIVATE -fno-rtti)
