/*!
 * \file
 * \details This file is part of https://github.com/kurogit/arduino_pong which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
#pragma once

#include <SPI.h>
#include <TFT.h>

namespace arduino_pong
{

class Rectangle;

class Renderer
{
public:
    enum class Color
    {
        White,
        Black
    };

public:
    Renderer();

    void clear();
    void render(const Rectangle& rect, Color color);
    void render(const char* text, int x, int y, Color color);
    void renderFieldLine();

private:
    void setupColor(Color color);

    TFT screen_;
};

}  // namespace arduino_pong
