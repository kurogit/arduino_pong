#include "GameField.hpp"

#include <Arduino.h>

#include "Renderer.hpp"

namespace
{

constexpr int FieldWidth = 160;
constexpr int FieldHeigt = 128;
constexpr int FieldCenter[] = {FieldWidth / 2, FieldHeigt / 2};

constexpr int LeftPaddleXPosition = 2;
constexpr int RightPaddleXPosition = FieldWidth - arduino_pong::Paddle::Width - 2;
constexpr int MaxPaddleYPosition = FieldHeigt - arduino_pong::Paddle::Height;

}  // namespace

namespace arduino_pong
{

GameField::GameField()
    : input_{},
      state_{{FieldCenter[0], FieldCenter[1]}, {{LeftPaddleXPosition, FieldCenter[1]}, {RightPaddleXPosition, FieldCenter[1]}}},
      oldState_{state_},
      init_{false}
{
}

void GameField::update()
{
    float leftInput = input_.getLeftPlayerInput();

    int newYPos = MaxPaddleYPosition * leftInput;

    oldState_ = state_;

    state_.paddles_[1].setYPos(newYPos);
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
}

}  // namespace arduino_pong
