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
    Rectangle bounds_{0, 0, 4, 4};
    float angle_ = 0.0f;
    float velocity_ = 0.0f;
};

}  // namespace arduino_pong
