/*!
 * \file
 * \details This file is part of https://github.com/kurogit/arduino_pong which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
#include <Arduino.h>
#include <pins_arduino.h>

#include "Game.hpp"

void setup();


int main()
{
    init();

    setup();

    arduino_pong::Game game;

    game.run();

    return 0;
}

void setup()
{
    Serial.begin(9600);
    Serial.write("setup ");

    pinMode(LED_BUILTIN, OUTPUT);
}
