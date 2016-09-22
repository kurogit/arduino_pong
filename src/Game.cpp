#include "Game.hpp"

#include <Arduino.h>

namespace
{

constexpr uint32_t MsPerUpdate = 16;

}  // namespace

namespace arduino_pong
{

void Game::run()
{

    uint32_t previous = millis();
    uint32_t lag = 0;

    while(true)
    {
        uint32_t current = millis();
        uint32_t elapsed = current - previous;
        previous = current;
        lag += elapsed;

        while(lag >= MsPerUpdate)
        {
            gameField_.update();
			lag -= MsPerUpdate;
        }

        gameField_.render();
    }
}

}  // namespace arduino_pong
