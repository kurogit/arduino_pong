/*!
 * \file
 * \details This file is part of https://github.com/kurogit/arduino_pong which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <Rectangle.hpp>

TEST_CASE("Constructor and getters")
{
	using arduino_pong::Rectangle;

	Rectangle rect{1, 2, 100, 50};

	CHECK(rect.x() == 1);
	CHECK(rect.y() == 2);
	CHECK(rect.width() == 100);
	CHECK(rect.height() == 50);

	SUBCASE("setters")
	{
		rect.setX(42);
		CHECK(rect.x() == 42);

		rect.setY(4711);
		CHECK(rect.y() == 4711);
	}
}
