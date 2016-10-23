/*!
 * \file
 * \details This file is part of https://github.com/kurogit/arduino_pong which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
#pragma once

#include "Ball.hpp"
#include "Paddle.hpp"

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
