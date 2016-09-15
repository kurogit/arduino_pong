cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(arduino_pong_test
  LANGUAGES CXX)

add_library(arduino_pong_test_lib STATIC "${arduino_pong_SOURCES}" "${arduino_pong_HEADERS}")

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE arduino_pong_test_lib)

enable_testing()

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
