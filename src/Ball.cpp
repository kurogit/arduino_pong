/*!
 * \file
 * \details This file is part of https://github.com/kurogit/arduino_pong which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
#include "Ball.hpp"

#include <math.h>

#include "Rectangle.hpp"

namespace
{
constexpr float degreeToRadians(float degree)
{
    return (degree * static_cast<float>(M_PI)) / 180.0f;
}
}  // namespace

namespace arduino_pong
{


Ball::Ball(float x, float y)
    : bounds_{x, y, Ball::Width, Ball::Heigt},
      angle_{0.0f},
      velocity_{0.0f}
{
}

const Rectangle& Ball::bounds() const
{
    return bounds_;
}

float Ball::angle() const
{
    return angle_;
}

float Ball::velocity() const
{
    return velocity_;
}

void Ball::setAngle(float newAngle)
{
    angle_ = newAngle;
}
void Ball::setVelocity(float newVelocity)
{
    velocity_ = newVelocity;
}
void Ball::setPosition(float x, float y)
{
    bounds_.setX(x);
    bounds_.setY(y);
}
void Ball::moveOneFrame()
{
    const auto x = bounds_.x();
    const auto y = bounds_.y();

    const float newX = x + velocity_ * static_cast<float>(cos(static_cast<double>(degreeToRadians(angle_))));
    const float newY = y + velocity_ * static_cast<float>(sin(static_cast<double>(degreeToRadians(angle_))));

    setPosition(newX, newY);
}

}  // namespace arduino_pong
