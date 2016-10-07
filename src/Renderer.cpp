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
    screen_.rect(rect.x(), rect.y(), rect.width(), rect.height());
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
