#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include "Game.h"

class Spaceship {

private:
  int lives;
  std::shared_ptr<Gamemanager>& gameManager;
public:
  int getLives() const;
  void subLives();
  Spaceship(std::shared_ptr<Gamemanager>& gameMan);
  ~Spaceship();
  sf::Texture texture;
  sf::Sprite sprite;
};


#endif // !SPACESHIP_H


