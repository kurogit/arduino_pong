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
    void renderFieldLine();

private:
	void setupColor(Color color);

    TFT screen_;
};

}  // namespace arduino_pong
