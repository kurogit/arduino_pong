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
