#pragma once

#include "GameField.hpp"

namespace arduino_pong
{

class Game
{
public:
    //! Run the game. Start the game loop.
    void run();

private:
	GameField gameField_;
};

}  // namespace arduino_pong
