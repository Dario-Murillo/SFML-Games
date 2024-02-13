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
  bool already_shoot;
  bool can_move;
  int valuePoints;
  sf::Sprite sprite;
  sf::RectangleShape bullet;
  Enemie(int type, std::shared_ptr<Gamemanager>& gameMan, float x, float y);
  ~Enemie();
};

#endif // !ENEMIE_H



