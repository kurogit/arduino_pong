#pragma once

namespace arduino_pong
{

class Renderer;

class GameField
{
public:
    void update();
    void render(Renderer& renderer);
};

}  // namespace arduino_pong
