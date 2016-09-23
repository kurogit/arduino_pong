#pragma once

#include <TFT.h>
#include <SPI.h>

namespace arduino_pong
{

class Rectangle;

class Renderer
{
public:
    Renderer();

    void clear();
    void render(const Rectangle& rect);
    void renderFieldLine();

private:
	TFT screen_;
};

}  // namespace arduino_pong
