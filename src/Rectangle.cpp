/*!
 * \file
 * \details This file is part of https://github.com/kurogit/arduino_pong which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
#include "Rectangle.hpp"

namespace arduino_pong
{

Rectangle::Rectangle(float x, float y, int width, int height)
    : x_{x},
      y_{y},
      width_{width},
      height_{height}
{
}

void Rectangle::setX(float newX)
{
    x_ = newX;
}

void Rectangle::setY(float newY)
{
    y_ = newY;
}

float Rectangle::x() const
{
    return x_;
}

float Rectangle::y() const
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
    {
        return true;
    }

    return (left.x() == right.x()) && (left.y() == right.y()) && (left.width() == right.width()) && (left.height() == right.height());
}

bool operator!=(const Rectangle& left, const Rectangle& right)
{
    return !(left == right);
}

}  // namespace arduino_pong
