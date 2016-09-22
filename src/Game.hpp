#pragma once

#include "GameField.hpp"
#include "Renderer.hpp"

namespace arduino_pong
{

class Game
{
public:
    //! Run the game. Start the game loop.
    void run();

private:
	GameField gameField_;
	Renderer renderer_;
};

}  // namespace arduino_pong
