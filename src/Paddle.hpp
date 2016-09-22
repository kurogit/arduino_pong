#pragma once

#include "Rectangle.hpp"

namespace arduino_pong
{

class Paddle
{
public:
    static constexpr int Width = 6;
    static constexpr int Height = 20;

public:
    Paddle(int x, int y);

    const Rectangle& bounds() const;

private:
    Rectangle bounds_;
};

}  // namespace arduino_pong
