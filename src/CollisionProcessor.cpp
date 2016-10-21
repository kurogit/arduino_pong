/*!
 * \file
 * \details This file is part of https://github.com/kurogit/arduino_pong which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
#include "CollisionProcessor.hpp"

#include "Rectangle.hpp"

namespace arduino_pong
{

bool CollisionProcessor::checkCollision(const Rectangle& rect1, const Rectangle& rect2)
{
    return rect1.x() < (rect2.x() + rect2.width())
           && (rect1.x() + rect1.width()) > rect2.x()
           && rect1.y() < (rect2.y() + rect2.height())
           && (rect1.height() + rect1.y()) > rect2.y();
}

}  // namespace arduino_pong
