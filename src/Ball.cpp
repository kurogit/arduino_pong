#include "Ball.hpp"

#include <math.h>

#include "Rectangle.hpp"

namespace
{
constexpr auto degreeToRadians(float degree)
{
    return (degree * M_PI) / 180.0f;
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

    setPosition(x + velocity_ * cos(degreeToRadians(angle_)), y + velocity_ * sin(degreeToRadians(angle_)));
}

}  // namespace arduino_pong
