#pragma once

namespace arduino_pong
{

class Input
{
public:
    Input();

    float getLeftPlayerInput() const;
    float getRightPlayerInput() const;
};

}  // namespace arduino_pong
