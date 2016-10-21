/*!
 * \file
 * \details This file is part of https://github.com/kurogit/arduino_pong which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
#include "Renderer.hpp"

#include "Rectangle.hpp"

namespace
{

constexpr int CSPin = 10;
constexpr int DCPin = 9;
constexpr int RESETPin = 8;


}  // namespace

namespace arduino_pong
{

Renderer::Renderer()
    : screen_{CSPin, DCPin, RESETPin}
{
    // build fix for arduino-cmake
    SPI.begin();

    screen_.begin();

    setupColor(Color::White);
    clear();

    renderFieldLine();
}

void Renderer::clear()
{
    screen_.background(0, 0, 0);
}

void Renderer::render(const Rectangle& rect, Color color)
{
    setupColor(color);
    screen_.rect(round(rect.x()), round(rect.y()), rect.width(), rect.height());
}

void Renderer::render(const char* text, int x, int y, Color color)
{
    setupColor(color);
    screen_.text(text, x, y);
}

void Renderer::renderFieldLine()
{
}

void Renderer::setupColor(Color color)
{
    int value = 0;
    switch(color)
    {
    case Renderer::Color::White:
    {
        value = 255;
        break;
    }
    case Renderer::Color::Black:
    {
        value = 0;
        break;
    }
    }

    screen_.stroke(value, value, value);
    screen_.fill(value, value, value);
}

}  // namespace arduino_pong
