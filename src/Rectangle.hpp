/*!
 * \file
 * \details This file is part of https://github.com/kurogit/arduino_pong which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
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
