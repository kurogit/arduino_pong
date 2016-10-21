/*!
 * \file
 * \details This file is part of https://github.com/kurogit/arduino_pong which is licensed under the MIT License.
 * \copyright 2016 Patrick Schwartz <kurogit@schwartzm.com>
 */
#pragma once

namespace arduino_pong
{

class Input
{
public:
    float getLeftPlayerInput() const;
    float getRightPlayerInput() const;
};

}  // namespace arduino_pong
