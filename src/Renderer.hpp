#pragma once

namespace arduino_pong
{

	class Rectangle;

class Renderer
{
public:
	void render(const Rectangle& rect);
	void renderFieldLine();
};

}  // namespace arduino_pong
