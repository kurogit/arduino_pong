/*!
 * \file
 * \details This file is part of https://github.com/kurogit/arduino_pong which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
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
    Ball(float x, float y);

    const Rectangle& bounds() const;
    float angle() const;
    float velocity() const;

    void setAngle(float newAngle);
    void setVelocity(float newVelocity);
    void setPosition(float x, float y);
    void moveOneFrame();

private:
    Rectangle bounds_;
    float angle_;
    float velocity_;
};

}  // namespace arduino_pong
