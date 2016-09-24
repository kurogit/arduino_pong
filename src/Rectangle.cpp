#include "Rectangle.hpp"

namespace arduino_pong
{

Rectangle::Rectangle(int x, int y, int width, int height)
    : x_{x},
      y_{y},
      width_{width},
      height_{height}
{
}

void Rectangle::setX(int newX)
{
	x_ = newX;
}

void Rectangle::setY(int newY)
{
	y_ = newY;
}

int Rectangle::x() const
{
    return x_;
}

int Rectangle::y() const
{
    return y_;
}

int Rectangle::width() const
{
    return width_;
}

int Rectangle::height() const
{
    return height_;
}

bool operator==(const Rectangle& left, const Rectangle& right)
{
	if(&left == &right)
		return true;

	return (left.x() == right.x()) && (left.y() == right.y()) && (left.width() == right.width()) && (left.height() == right.height());
}

bool operator!=(const Rectangle& left, const Rectangle& right)
{
	return !(left == right);
}

}  // namespace arduino_pong
