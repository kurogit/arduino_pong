#include "Game.hpp"

#include <Arduino.h>

namespace
{

constexpr uint32_t MsPerUpdate = 30;

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

#ifdef ARDUINO_PONG_DEBUG
        Serial.println(delayValue);
#endif

        delay(delayValue < 0 ? 0 : delayValue);
    }
}

}  // namespace arduino_pong
