#pragma once

#include "GameState.hpp"
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
    void reset();

private:
    void handleCollision(int paddleNum);
	void resetBall(float angle);

	void renderCurrentPoints(Renderer& renderer);

    Input input_;
    GameState state_;
    GameState oldState_;
    bool init_;
};

}  // namespace arduino_pong
