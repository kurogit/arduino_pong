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
      ball_{FieldCenter[0], FieldCenter[1]},
      paddles_{{LeftPaddleXPosition, FieldCenter[1]}, {RightPaddleXPosition, FieldCenter[1]}}
{
}

void GameField::update()
{
    float leftInput = input_.getLeftPlayerInput();

	int newYPos = MaxPaddleYPosition * leftInput;

	paddles_[0].setYPos(newYPos);
}

void GameField::render(Renderer& renderer)
{
	renderer.clear();
    renderer.renderFieldLine();

    renderer.render(ball_.bounds());
    renderer.render(paddles_[0].bounds());
    renderer.render(paddles_[1].bounds());
}

}  // namespace arduino_pong
