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
    Paddle(float x, float y);

    const Rectangle& bounds() const;

    void setYPos(float newPos);

private:
    Rectangle bounds_;
};

}  // namespace arduino_pong
