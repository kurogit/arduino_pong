/*!
 * \file
 * \details This file is part of https://github.com/kurogit/arduino_pong which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
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

TEST_CASE("movement")
{
    using arduino_pong::Ball;

    Ball ball{0, 0};

    const auto& bounds = ball.bounds();

    SUBCASE("velocity = 1")
    {
        // Set velocity to 1 for easier testing
        ball.setVelocity(1.0f);
        CHECK(ball.velocity() == 1.0f);

        SUBCASE("angle = 180")
        {
            ball.setAngle(180.0f);

            ball.moveOneFrame();

            CHECK(bounds.x() == doctest::Approx(-1.0f));
            CHECK(bounds.y() == doctest::Approx(0.0f));
        }
    }
}
