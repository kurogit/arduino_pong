#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <Ball.hpp>
#include <Rectangle.hpp>

TEST_CASE("Constructor and getters")
{
	using arduino_pong::Ball;

	Ball ball{1, 2};

	const auto& bounds = ball.bounds();
	CHECK(bounds.x() == 1);
	CHECK(bounds.y() == 2);
	CHECK(bounds.width() == 4);
	CHECK(bounds.height() == 4);

	CHECK(ball.angle() == 0.0f);
	CHECK(ball.velocity() == 0.0f);

}
