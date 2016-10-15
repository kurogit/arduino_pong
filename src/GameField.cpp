#include "GameField.hpp"

#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>

#include "CollisionProcessor.hpp"
#include "Renderer.hpp"

namespace
{

constexpr int FieldWidth = 160;
constexpr int FieldHeigt = 128;
constexpr int FieldCenter[] = {FieldWidth / 2, FieldHeigt / 2};

constexpr int LeftPaddleXPosition = 2;
constexpr int RightPaddleXPosition = FieldWidth - arduino_pong::Paddle::Width - 2;
constexpr int MaxPaddleYPosition = FieldHeigt - arduino_pong::Paddle::Height;

constexpr float BallDefaultVelocity = 1.0f;
constexpr float BallVelocityStep = 0.5f;


}  // namespace

namespace arduino_pong
{

GameField::GameField()
    : input_{},
      state_{{FieldCenter[0], FieldCenter[1]}, {{LeftPaddleXPosition, FieldCenter[1]}, {RightPaddleXPosition, FieldCenter[1]}}, 0, 0},
      oldState_{state_},
      init_{false}
{
    // Set initial ball speed and angle
    reset();
}

void GameField::reset()
{
    resetBall(180.0f);

    state_.pointsLeft = 0;
    state_.pointsRight = 0;

    init_ = false;
}

void GameField::resetBall(float angle)
{
    state_.ball_.setAngle(angle);
    state_.ball_.setVelocity(BallDefaultVelocity);
    state_.ball_.setPosition(FieldCenter[0], FieldCenter[1]);
}

void GameField::update()
{
    oldState_ = state_;

    // Movement Paddles
    float input = input_.getLeftPlayerInput();
    int newYPos = MaxPaddleYPosition * input;
    // The screen is actually upside down. left = 1, right = 0
    state_.paddles_[1].setYPos(newYPos);

    input = input_.getRightPlayerInput();
    newYPos = MaxPaddleYPosition * input;
    state_.paddles_[0].setYPos(newYPos);

    Ball& ball = state_.ball_;

    // Movement Ball
    ball.moveOneFrame();

    if(ball.bounds().y() < 0)
    {
        ball.setPosition(ball.bounds().x(), 1);
        ball.setAngle(-ball.angle());
    }
    else if(ball.bounds().y() + Ball::Heigt >= FieldHeigt)
    {
        ball.setPosition(ball.bounds().x(), FieldHeigt - Ball::Heigt - 1);
        ball.setAngle(-ball.angle());
    }
    else if(ball.bounds().x() <= 0)
    {
        ++state_.pointsRight;
        resetBall(0.0f);
    }
    else if(ball.bounds().x() >= FieldWidth)
    {
        ++state_.pointsLeft;
        resetBall(180.0f);
    }

    handleCollision(0);
    handleCollision(1);
}

void GameField::handleCollision(int paddleNum)
{
    static constexpr auto LeftPaddleUpperRight = LeftPaddleXPosition + Paddle::Width;
    static constexpr auto MaxBallSpeed = 9.0f;
    static constexpr auto MaxBallAngle = 55;

    Ball& ball = state_.ball_;
    Paddle& paddle = state_.paddles_[paddleNum];
    if(CollisionProcessor::checkCollision(ball.bounds(), paddle.bounds()))
    {
        const auto collisionY = ball.bounds().y() + Ball::Heigt / 2;
        const auto relativeY = paddle.bounds().y() + (Paddle::Height / 2) - collisionY;
        const float normalizedRelativeY = relativeY / (Paddle::Height / 2.0f);
        const auto newAngle = normalizedRelativeY * MaxBallAngle;

        ball.setAngle(paddleNum == 0 ? newAngle : 180.0f - newAngle);

        // Only increase ball speed if the maximum speed is not reached yet
        const float newBallSpeed = ball.velocity() + BallVelocityStep;
        if(newBallSpeed <= MaxBallSpeed)
        {
            ball.setVelocity(newBallSpeed);
        }

        if(paddleNum == 0)
        {
            ball.setPosition(LeftPaddleUpperRight, ball.bounds().y());
        }
        else
        {
            ball.setPosition(RightPaddleXPosition - Ball::Width, ball.bounds().y());
        }
    }
}

void GameField::render(Renderer& renderer)
{
    if(!init_)
    {
        renderer.clear();
        renderer.render(state_.ball_.bounds(), Renderer::Color::White);
        renderer.render(state_.paddles_[0].bounds(), Renderer::Color::White);
        renderer.render(state_.paddles_[1].bounds(), Renderer::Color::White);

        renderCurrentPoints(renderer);

        init_ = true;
    }

    if(oldState_.ball_.bounds() != state_.ball_.bounds())
    {
        renderer.render(oldState_.ball_.bounds(), Renderer::Color::Black);
        renderer.render(state_.ball_.bounds(), Renderer::Color::White);
    }
    if(oldState_.paddles_[0].bounds() != state_.paddles_[0].bounds())
    {
        renderer.render(oldState_.paddles_[0].bounds(), Renderer::Color::Black);
        renderer.render(state_.paddles_[0].bounds(), Renderer::Color::White);
    }
    if(oldState_.paddles_[1].bounds() != state_.paddles_[1].bounds())
    {
        renderer.render(oldState_.paddles_[1].bounds(), Renderer::Color::Black);
        renderer.render(state_.paddles_[1].bounds(), Renderer::Color::White);
    }
    if(oldState_.pointsLeft != state_.pointsLeft || oldState_.pointsRight != state_.pointsRight)
    {
        renderCurrentPoints(renderer);
    }
#ifdef ARDUINO_PONG_DEBUG
    // Render origin for testing
    renderer.render(Rectangle{0, 0, 2, 2}, Renderer::Color::White);

    // Render some debug stuff
    if(state_.ball_.velocity() != oldState_.ball_.velocity())
    {
        char buf[20]{};
        // Turns out avr-libc cant printf floating point numbers
        sprintf(static_cast<char*>(buf), "bs: %d", static_cast<int>(state_.ball_.velocity() * 10));

        renderer.render(Rectangle{5, 0, 100, 10}, Renderer::Color::Black);
        renderer.render(static_cast<char*>(buf), 5, 0, Renderer::Color::White);
    }
    if(state_.ball_.angle() != oldState_.ball_.angle())
    {
        char buf[20]{};
        // Turns out avr-libc cant printf floating point numbers
        sprintf(static_cast<char*>(buf), "ba: %d", static_cast<int>(state_.ball_.angle() * 10));

        renderer.render(Rectangle{5, 10, 100, 10}, Renderer::Color::Black);
        renderer.render(static_cast<char*>(buf), 5, 10, Renderer::Color::White);
    }
#endif
}

void GameField::renderCurrentPoints(Renderer& renderer)
{
    static constexpr auto MaxSize = 4;
    static constexpr auto DistanceToCenter = 20;
    static constexpr auto PointsLeftX = FieldCenter[0] - DistanceToCenter - MaxSize;
    static constexpr auto PointsRightX = FieldCenter[0] + DistanceToCenter;
    static constexpr auto PointsY = 20;

    renderer.render({PointsLeftX, PointsY, PointsRightX + MaxSize - PointsLeftX + 1, 10}, Renderer::Color::Black);

    char buf[MaxSize];
    const char* textToRender = itoa(state_.pointsLeft, static_cast<char*>(buf), 10);
    renderer.render(textToRender, PointsLeftX, PointsY, Renderer::Color::White);
    textToRender = itoa(state_.pointsRight, static_cast<char*>(buf), 10);
    renderer.render(textToRender, PointsRightX, PointsY, Renderer::Color::White);
}

}  // namespace arduino_pong
