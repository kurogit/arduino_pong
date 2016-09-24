#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <Paddle.hpp>
#include <Rectangle.hpp>

TEST_CASE("Constructor and getters")
{
	using arduino_pong::Paddle;

	Paddle paddle{1, 2};

	const auto& bounds = paddle.bounds();
	CHECK(bounds.x() == 1);
	CHECK(bounds.y() == 2);
	CHECK(bounds.width() == 6);
	CHECK(bounds.height() == 20);

	SUBCASE("setters")
	{
		paddle.setYPos(42);

		CHECK(bounds.y() == 42);
	}
}
