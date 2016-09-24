#include "Game.hpp"

#include <Arduino.h>

namespace
{

constexpr uint32_t MsPerUpdate = 200;

}  // namespace

namespace arduino_pong
{

void Game::run()
{
    while(true)
    {
        uint32_t start = millis();

        gameField_.update();
        gameField_.render(renderer_);

        int32_t delayValue = start + MsPerUpdate - millis();
        //Serial.println(delayValue);
        delay(delayValue < 0 ? 0 : delayValue);
    }
}

}  // namespace arduino_pong
