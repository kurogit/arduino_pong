#include "Paddle.hpp"

namespace arduino_pong
{

Paddle::Paddle(int x, int y)
    : bounds_{x, y, Paddle::Width, Paddle::Height}
{
}

void Paddle::setYPos(int newPos)
{
	bounds_.setY(newPos);
}

const Rectangle& Paddle::bounds() const
{
    return bounds_;
}

}  // namespace arduino_pong
