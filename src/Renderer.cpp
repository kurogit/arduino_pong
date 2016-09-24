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

	screen_.stroke(0, 0, 0);
	screen_.fill(0, 0, 0);

    clear();
}

void Renderer::clear()
{
    screen_.background(255, 255, 255);
}

void Renderer::render(const Rectangle& rect)
{
	screen_.rect(rect.x(), rect.y(), rect.width(), rect.height());
}

void Renderer::renderFieldLine()
{
}

}  // namespace arduino_pong
