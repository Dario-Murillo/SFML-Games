#include "Spaceship.h"

int Spaceship::getLives() const {
  return this->lives;
}

void Spaceship::subLives() {
  this->lives -= 1;
}

Spaceship::Spaceship(std::shared_ptr<Gamemanager>& gameMan) : gameManager(gameMan) {
  this->lives = 3;
  if (!this->texture.loadFromFile("Images/spaceship.jpg")) {
    // TODO:
    // Handle error
  }
  this->sprite.setTexture(this->texture);
  this->sprite.setScale(sf::Vector2f(.05, .05));
  this->sprite.setPosition( static_cast<float> (this->gameManager->window->getSize().x / 2), 
                            static_cast<float> (this->gameManager->window->getSize().y) - this->sprite.getGlobalBounds().height);
}

Spaceship::~Spaceship() { }
