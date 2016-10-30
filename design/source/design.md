---
title: Arduino Pong
---

## The Project
In this project i am going to implement Pong from scratch for an Arduino Uno with an [Arduino TFT].

My project goals are the following:

* Learn about programming for embedded hardware (Arduino)
* Generally raise my programming experience

This document is the initial design for the project. Some things might be different in the code then represented below.

This project is licensed under the MIT License. See [LICENSE](LICENSE).

[Arduino TFT]: <https://www.arduino.cc/en/Guide/TFT>

### Tools
The following tools and libraries will be used in the project:

* CMake with [Arduino CMake]
* Arduino SDK and TFT library
* [doctest] for unit tests

Arduino CMake uses gcc-avr to compile the c++ code. This means that exceptions are disabled by default(-fno-exceptions).

I additionally apply the following restrictions:

* No use of RTTI (-fno-rtti). RTTI costs time and space. I don't plan to use any or much inheritance.
* No dynamic memory allocation. While Arduino supports `operator new`{.cpp}, i will not use it.

[Arduino CMake]: <https://github.com/queezythegreat/arduino-cmake>
[doctest]: <https://github.com/onqtam/doctest>

## Pong
\ditaa(source/figures/gen/pong_complete)(Pong)
~~~~
+------------------------------+
|+--+                          |
||  |                          |
||  |                          |
||  |                      +--+|
||  |             /-\      |  ||
|+--+             \-/      |  ||
|                          |  ||
|                          |  ||
|                          +--+|
|                              |
|                              |
|                              |
+------------------------------+
~~~~

Pong is a simple game the players control paddles to hit the ball back to the opponent. If a player fails to catch the ball, the opponent receives one point. The points if the player are shown as text inside the players field.

The following objects make up the game:

* Two paddles
* A ball

### Details

Since the ball can hit the paddles, collision checks need to be performed. The original Pong had segmented paddles. The segment the ball hits determents the return angle of the ball. Hitting the ball with the center of the paddle returns the ball with an 90° angle. Other parts of the paddle return the ball at smaller angles.

The Game is targeted to run on the Arduino TFT. This means that the dimensions of the screen are known beforehand and will never change. Compared to desktop development, this makes things easier. The screen has dimensions of 160 x 128 :

\ditaa(source/figures/gen/screen)(The TFT-Screen)
~~~~
+--------------+ -
|              | |
|              | |
|              | |128
|              | |
|              | |
+--------------+ -

|-----160------|
~~~~

We can now define:

**Paddle**
  : * Width:  6px
    * Height: 20px

**Ball**
  : * Width: 4px
    * Height: 4px

The following shows the relative sizes of the objects:

![Pictures showing relatives sizes](source/figures/field_drawn.png){width=200% height=200%}

# Implementation Design
## Classes

The high level design is shown in the following diagram:

\uml(source/figures/gen/pong)(Top-level class diagram)
~~~~
namespace pong {
    class Paddle
    class Ball
    class GameField
    class Game
    class Renderer
    class CollisionProcessor
    class Input

    GameField "1" *-- "2" Paddle
    GameField "1" *-- "1" Ball

    Game o-- GameField

    Renderer ..> Paddle : draws
    Renderer ..> Ball : draws

    GameField ..> CollisionProcessor : <<uses>>
    GameField ..> Input : <<uses>>
}
~~~~

### Game
\uml(source/figures/gen/uml_game)(Class diagram of [Game](#game))
~~~~
class Game {
    - gameField_ : GameField
    - renderer_ : Renderer
    + run() : void
}
~~~~

The Game class includes the [Game Loop]. It has an instance of [GameField](#gamefield) and will call `update()` and `render()` methods on it. `run()` will be directly called from `main` and represents the main loop of the program.

Pseudo code:

~~~~{.cpp}
void Game::run()
{
    gameField_.update();
    gameField_.render(renderer_);
}
~~~~

### GameField
\uml(source/figures/gen/uml_gamefield)(Class diagram for [GameField](#gamefield))
~~~
class GameField {
    - paddles_ : Paddle[2]
    - ball_ : Ball
    - collision_ : CollisionProcessor

    + update() : void
    + render(renderer : Renderer&) : void
}
~~~

GameField represents the pong field. It contains the ball and the paddles. In `update()` and `render()` it handles movement and collision of the ball and the paddles. The `render()` method uses the `Renderer` to draw the ball and paddles on the screen.

Pseudo code:

~~~~{.cpp}
void GameField::update()
{
    movePaddlesAccordingToInput();
    moveBall();
    checkBallCollision();
}
void GameField::render(Renderer& renderer)
{
    renderer.render(ball_);
    renderer.render(paddles_[0]);
    renderer.render(paddles_[1]);
}
~~~~

### Ball and Paddle

We can model both of these with rectangles. In addition of width and height, the Rectangle class gets x and y for position:

\uml(source/figures/gen/uml_rectangle)(Class diagram Rectangle)
~~~~
class Rectangle {
    -x : int
    -y : int
    -width : int
    -height : int
    --
    getters and setters
}
~~~~

Ball and Paddle are then defined as follows:

\uml(source/figures/gen/uml_ball)(Class diagram Ball)
~~~~
class Ball {
    -bounds_ : Rectangle
    -angle_ : float
    -velocity_ : float
    --
    getters and setters
}
~~~~

\uml(source/figures/gen/uml_paddle)(Paddle diagram Ball)
~~~~
class Paddle {
    -bounds_ : Rectangle
    --
    getters and setters
}
~~~~

[Game Loop]: <http://gameprogrammingpatterns.com/game-loop.html>

### CollisionProcessor

\uml(source/figures/gen/uml_collision)(Class diagram CollisionProcessor)
~~~~
class ColisionProcessor {
    +bool checkCollision(l : const Rectangle&, r : const Rectangle&)
}
~~~~

Checks collisions between rectangles. `checkCollision()` checks if the two rectangles collide in any way. This includes one rectangle being contained in another.

### Renderer

\uml(source/figures/gen/uml_render)(Class diagram Renderer)
~~~~
class Renderer {
    +render(rect: const Rectangle&) : void
	+renderFieldLine() : void
}
~~~~

Renderer renders various thing to the screen.
