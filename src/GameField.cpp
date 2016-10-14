#include "GameField.hpp"

#include <Arduino.h>
#include <stdio.h>

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
      state_{{FieldCenter[0], FieldCenter[1]}, {{LeftPaddleXPosition, FieldCenter[1]}, {RightPaddleXPosition, FieldCenter[1]}}},
      oldState_{state_},
      init_{false}
{
    // Set initial ball speed and angle

    state_.ball_.setAngle(180.0f);
    state_.ball_.setVelocity(BallDefaultVelocity);
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

    // Check if ball is outside the field
    if(!CollisionProcessor::checkCollision(Rectangle{0, 0, FieldWidth, FieldHeigt}, ball.bounds()))
    {
		const bool leftOut = ball.bounds().x() <= FieldCenter[0];

        ball.setAngle(leftOut ? 0.0f : 180.0f);
        ball.setVelocity(BallDefaultVelocity);
		ball.setPosition(FieldCenter[0], FieldCenter[1]);
		return;
    }

    handleCollision(0);
    handleCollision(1);
}

void GameField::handleCollision(int paddleNum)
{
    static constexpr auto LeftPaddleUpperRight = LeftPaddleXPosition + Paddle::Width;
    static constexpr auto MaxBallSpeed = 9.0f;

    Ball& ball = state_.ball_;
    if(CollisionProcessor::checkCollision(ball.bounds(), state_.paddles_[paddleNum].bounds()))
    {
        ball.setAngle(180.0f - ball.angle());

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
        renderer.render(state_.ball_.bounds(), Renderer::Color::White);
        renderer.render(state_.paddles_[0].bounds(), Renderer::Color::White);
        renderer.render(state_.paddles_[1].bounds(), Renderer::Color::White);
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

#ifdef ARDUINO_PONG_DEBUG
    // Render origin for testing
    renderer.render(Rectangle{0, 0, 2, 2}, Renderer::Color::White);

    // Render some debug stuff
    if(state_.ball_.velocity() != oldState_.ball_.velocity())
    {
        char buf[20]{};
        // Turns out avr-libc cant printf floating point numbers
        sprintf(static_cast<char*>(buf), "bs: %d", static_cast<int>(state_.ball_.velocity() * 10));

        renderer.render(Rectangle{5, 0, 100, 5}, Renderer::Color::Black);
        renderer.render(static_cast<char*>(buf), 5, 0, Renderer::Color::White);
    }
#endif
}

}  // namespace arduino_pong
