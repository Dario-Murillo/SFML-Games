#include "Enemie.h"

Enemie::Enemie(int type, std::shared_ptr<Gamemanager>& gameMan, float x, float y) : gameManager(gameMan), valuePoints(0), x(x), y(y) {
  this->already_shoot = false;
  this->can_move = true;
  this->bullet.setScale(1.f, 1.f);
  this->bullet.setSize(sf::Vector2f(3.f, 15.f));
  this->bullet.setFillColor(sf::Color::Red);
  switch (type) {
  case 1:
    if (this->texture.loadFromFile("Images/alien1.png")) {
      this->sprite.setTexture(this->texture);
      this->sprite.setScale(sf::Vector2f(.2, .2));
      this->sprite.setPosition(sf::Vector2f(this->x, this->y));
      this->sprite.setColor(sf::Color::Cyan);
      this->valuePoints = 30;
    }
    break;
  case 2:
    if (this->texture.loadFromFile("Images/alien1.png")) {
      this->sprite.setTexture(this->texture);
      this->sprite.setScale(sf::Vector2f(.2, .2));
      this->sprite.setPosition(sf::Vector2f(this->x, this->y));
      this->sprite.setColor(sf::Color::Blue);
      this->valuePoints = 20;
    }
    break;
  case 3:
    if (this->texture.loadFromFile("Images/alien1.png")) {
      this->sprite.setTexture(this->texture);
      this->sprite.setScale(sf::Vector2f(.2, .2));
      this->sprite.setPosition(sf::Vector2f(this->x, this->y));
      this->sprite.setColor(sf::Color::Green);
      this->valuePoints = 10;
    }
    break;
  default:
    if (this->texture.loadFromFile("Images/alien1.png")) {
      this->sprite.setTexture(this->texture);
      this->sprite.setScale(sf::Vector2f(.2, .2));
      this->sprite.setPosition(sf::Vector2f(this->x, this->y));
      this->valuePoints = 10;
    }
	break;
  }
}

Enemie::~Enemie() { }
