#ifndef ENEMIE_H
#define ENEMIE_H

#include <SFML/Graphics.hpp>
#include "Game.h"

class Enemie {

private:
  sf::Texture texture;
  std::shared_ptr<Gamemanager>& gameManager;
  float x;
  float y;
public:
  int valuePoints;
  sf::Sprite sprite;
  Enemie(int type, std::shared_ptr<Gamemanager>& gameMan, float x, float y);
  ~Enemie();
};

#endif // !ENEMIE_H



