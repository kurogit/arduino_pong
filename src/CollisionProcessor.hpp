/*!
 * \file
 * \details This file is part of https://github.com/kurogit/arduino_pong which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
#pragma once

namespace arduino_pong
{

class Rectangle;

struct CollisionProcessor
{
	/*!
	 *  \brief Checks if there is currently a collision between \a rect1 and \a rect2.
	 *  \details A collision occurs when some part of \a rect1 is inside \a rect2, or the other way around. A rectangle completly contained within the other also counts as a collision.
	 *  \returns \c true if the rectangles currently collide.
	 */
    static bool checkCollision(const Rectangle& rect1, const Rectangle& rect2);
};

}  // namespace arduino_pong
