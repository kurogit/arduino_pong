/*!
 * \file
 * \details This file is part of https://github.com/kurogit/arduino_pong which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
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
