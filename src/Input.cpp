#include "Input.hpp"

#include <Arduino.h>

namespace
{

constexpr auto InputPin = A0;

}  // namespace

namespace arduino_pong
{

Input::Input()
{
}

float Input::getLeftPlayerInput() const
{
	static constexpr float maxValue = 1023.0f;

	int value = analogRead(InputPin);

	float floatValue = static_cast<float>(value) / maxValue;

	return floatValue;
}

float Input::getRightPlayerInput() const
{
}

}  // namespace arduino_pong
