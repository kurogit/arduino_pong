#pragma once

namespace arduino_pong
{

class Rectangle
{
public:
    Rectangle(float x, float y, int width, int height);

    void setX(float newX);
    void setY(float newY);

    float x() const;
    float y() const;
    int width() const;
    int height() const;

private:
    float x_ = 0;
    float y_ = 0;
    int width_ = 0;
    int height_ = 0;
};

bool operator==(const Rectangle& left, const Rectangle& right);
bool operator!=(const Rectangle& left, const Rectangle& right);

}  // namespace arduino_pong
