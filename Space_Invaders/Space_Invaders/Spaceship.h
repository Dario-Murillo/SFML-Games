#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include "Game.h"

// Class that manages the object of the main player
class Spaceship {
private:
  // The amount of lives the player has, initially is 3
  int lives;
  // Pointer to the main controller object of the game
  std::shared_ptr<Gamemanager>& gameManager;
public:
  // Return the amount of lives left
  int getLives() const;
  // Substracts one life from the current amount
  void subLives();
  /*
    Constructor:
    @param gameMan, Pointer to the main controller object of the game
  */
  Spaceship(std::shared_ptr<Gamemanager>& gameMan);
  // Default destructor
  ~Spaceship();
  // Texture to load to the sprite
  sf::Texture texture;
  // Sprite (look) of the player
  sf::Sprite sprite;
};

#endif // !SPACESHIP_H
