#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <CollisionProcessor.hpp>
#include <Rectangle.hpp>

using arduino_pong::CollisionProcessor;
using arduino_pong::Rectangle;

TEST_CASE("non colliding rectangles")
{
    Rectangle rect1{0, 0, 100, 50};
    Rectangle rect2{1000, 1000, 100, 50};

    CHECK_FALSE(CollisionProcessor::checkCollision(rect1, rect2));
    CHECK_FALSE(CollisionProcessor::checkCollision(rect2, rect1));
}

TEST_CASE("colliding rectangles")
{
	Rectangle rect1{0, 0, 100, 100};
	Rectangle rect2{50, 50, 100, 100};

	CHECK(CollisionProcessor::checkCollision(rect1, rect2));
	CHECK(CollisionProcessor::checkCollision(rect2, rect1));
}

TEST_CASE("rect1 inside rect2")
{
	Rectangle rect2{0, 0, 100, 100};
	Rectangle rect1{25, 25, 50, 50};

	CHECK(CollisionProcessor::checkCollision(rect1, rect2));
	CHECK(CollisionProcessor::checkCollision(rect2, rect1));
}
