#include "GameField.hpp"

#include <Arduino.h>

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

    // Render origin for testing
    renderer.render(Rectangle{0, 0, 2, 2}, Renderer::Color::White);

}

}  // namespace arduino_pong
