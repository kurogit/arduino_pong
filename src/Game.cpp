#include "Game.hpp"

namespace arduino_pong
{

void Game::run()
{
    while(true)
    {
        gameField_.update();
        gameField_.render();
    }
}

}  // namespace arduino_pong
