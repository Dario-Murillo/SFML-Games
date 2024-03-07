#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

/* Pure abstract class for inheritance
  This class will be used for other classes to have the properties of a screen
*/
class Screen {
public:
  /* Main method that is gonna call update and render*/
  virtual void run() = 0;
  /* Function that will poll the events, it's called by the update function */
  virtual void poll() = 0;
  /* Updates and manages the game logic */
  virtual void update() = 0;
  /* Draws the figures, texts, sprites, etc... */
  virtual void render() = 0;
};

#endif // !SCREEN_H

