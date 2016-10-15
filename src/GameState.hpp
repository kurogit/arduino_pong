#pragma once

#include "Ball.hpp"
#include "Paddle.hpp"
#include "Rectangle.hpp"

namespace arduino_pong
{

struct GameState
{
	Ball ball_;
	Paddle paddles_[2];
	int pointsLeft;
	int pointsRight;
};

}  // namespace asm
