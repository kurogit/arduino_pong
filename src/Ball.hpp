#pragma once

#include "Rectangle.hpp"

namespace arduino_pong
{

class Ball
{
public:
    static constexpr int Width = 4;
    static constexpr int Heigt = 4;
public:
    Ball(int x, int y);

	const Rectangle& bounds() const;
	float angle() const;
	float velocity() const;
private:
    Rectangle bounds_;
    float angle_;
    float velocity_;
};

}  // namespace arduino_pong
