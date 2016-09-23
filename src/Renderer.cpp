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
    screen_.begin();

	screen_.stroke(255, 255, 255);
	screen_.fill(255, 255, 255);

    clear();
}

void Renderer::clear()
{
    screen_.background(0, 0, 0);
}

void Renderer::render(const Rectangle& rect)
{
	screen_.rect(rect.x(), rect.y(), rect.width(), rect.height());
}

void Renderer::renderFieldLine()
{
}

}  // namespace arduino_pong
