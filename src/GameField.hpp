#pragma once

#include "Ball.hpp"
#include "Paddle.hpp"

namespace arduino_pong
{

class Renderer;

class GameField
{
public:
	GameField();

    void update();
    void render(Renderer& renderer);
private:
	Ball ball_;
	Paddle paddles_[2];
};

}  // namespace arduino_pong
