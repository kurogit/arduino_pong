/*!
 * \file
 * \details This file is part of https://github.com/kurogit/arduino_pong which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
#include "Paddle.hpp"

namespace arduino_pong
{

Paddle::Paddle(float x, float y)
    : bounds_{x, y, Paddle::Width, Paddle::Height}
{
}

void Paddle::setYPos(float newPos)
{
    bounds_.setY(newPos);
}

const Rectangle& Paddle::bounds() const
{
    return bounds_;
}

}  // namespace arduino_pong
