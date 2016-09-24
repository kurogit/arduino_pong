#pragma once

#include "Ball.hpp"
#include "Paddle.hpp"
#include "Input.hpp"

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
	Input input_;
	Ball ball_;
	Paddle paddles_[2];
};

}  // namespace arduino_pong
