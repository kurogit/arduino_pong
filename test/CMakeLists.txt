cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(arduino_pong_test
  LANGUAGES CXX)

set(arduino_pong_test_SOURCES
  src/RectangleTest.cpp
  src/BallTest.cpp
  src/PaddleTest.cpp
  src/CollisionProcessorTest.cpp)

# Get doctest
file(DOWNLOAD "https://raw.githubusercontent.com/onqtam/doctest/master/doctest/doctest.h" "${CMAKE_CURRENT_BINARY_DIR}/doctest/doctest.h")

foreach(_test_src ${arduino_pong_test_SOURCES})
  get_filename_component(_test_name ${_test_src} NAME_WE)
  add_executable(${_test_name} ${_test_src})
  target_include_directories(${_test_name} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/doctest")
  target_link_libraries(${_test_name} PRIVATE arduino_pong)
  set_target_properties(${_test_name}
    PROPERTIES
    CXX_INCLUDE_WHAT_YOU_USE "include-what-you-use"
    CXX_CLANG_TIDY "clang-tidy")

  add_test(NAME ${_test_name} COMMAND ${_test_name})
endforeach()
