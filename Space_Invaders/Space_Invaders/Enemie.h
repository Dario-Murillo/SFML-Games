#ifndef ENEMIE_H
#define ENEMIE_H

#include <SFML/Graphics.hpp>
#include "Game.h"

/*
  Class that manages the enemie objects of the game
*/
class Enemie {
private:
  // Texture to load to the sprite
  sf::Texture texture;
  // Pointer to the main controller object of the game
  std::shared_ptr<Gamemanager>& gameManager;
  // Initial position of the enemie in the horizontal axis
  float x;
  // Initial position of the enemie in the vertical axis
  float y;
public:
  // The amount of points each enemie is worth
  int valuePoints;
  // Sprite that will display the texture
  sf::Sprite sprite;
  /*
    Constructor
    @param type, Indicate what type of enemie we want to construct
    this will determine the amount of points worth and the color of the sprite
    @param gameMan, Pointer to the main controller object of the game
    @param x, Initial position of the enemie in the horizontal axis
    @param y, Initial position of the enemie in the vertical axis
  */
  Enemie(int type, std::shared_ptr<Gamemanager>& gameMan, float x, float y);
  ~Enemie();
};

#endif // !ENEMIE_H
