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

}  // namespace arduino_pong
