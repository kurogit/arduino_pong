#include "Input.hpp"

#include <Arduino.h>

namespace
{

constexpr uint8_t InputPinLeft = A0;
constexpr uint8_t InputPinRight = A1;

float processInput(uint8_t pin)
{
    static constexpr float maxValue = 1023.0f;

    int value = analogRead(pin);

    float floatValue = static_cast<float>(value) / maxValue;

    return floatValue;
}

}  // namespace

namespace arduino_pong
{

Input::Input()
{
}

float Input::getLeftPlayerInput() const
{
    return processInput(InputPinLeft);
}

float Input::getRightPlayerInput() const
{
	return processInput(InputPinRight);
}

}  // namespace arduino_pong
