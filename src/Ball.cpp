#include "Ball.hpp"

namespace arduino_pong
{

class Rectangle;

Ball::Ball(int x, int y)
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

}  // namespace arduino_pong
