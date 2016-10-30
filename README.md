Arduino Pong
=======

The Project
-----------

In this project i am going to implement Pong from scratch for an Arduino Uno with an [Arduino TFT](https://www.arduino.cc/en/Guide/TFT).

My project goals are the following:

-   Learn about programming for embedded hardware (Arduino)
-   Generally raise my programming experience

This project is licensed under the MIT License. See [LICENSE](LICENSE).

### Tools

The following tools and libraries will be used in the project:

-   CMake with [Arduino CMake](https://github.com/queezythegreat/arduino-cmake)
-   Arduino SDK and TFT library
-   [doctest](https://github.com/onqtam/doctest) for unit tests

Arduino CMake uses gcc-avr to compile the c++ code. This means that exceptions are disabled by default(-fno-exceptions).

I additionally apply the following restrictions:

-   No use of RTTI (-fno-rtti). RTTI costs time and space. I don’t plan to use any or much inheritance.
-   No dynamic memory allocation. While Arduino supports `operator new`, i will not use it.

### The Game and Design

The initial design for the project can be found [here](design/arduino_pong_design.md). Some things might be different in the code then presented there.
