#pragma once

namespace arduino_pong
{

class Rectangle
{
public:
	Rectangle(int x, int y, int width, int height);

	void setX(int newX);
	void setY(int newY);

	int x() const;
	int y() const;
	int width() const;
	int height() const;

private:
	int x_ = 0;
	int y_ = 0;
	int width_ = 0;
	int height_ = 0;
};

}  // namespace arduino_pong
