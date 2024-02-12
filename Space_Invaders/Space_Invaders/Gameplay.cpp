#include "Gameplay.h"


void Gameplay::initVars() {
  this->moveLeft = false;
  this->moveRight = false;
}

void Gameplay::updateHeroe() {
  if (this->moveLeft) {
	this->heroe->sprite.move(5.f, 0.f);
  }
  if (this->moveRight && this->heroe->sprite.getPosition().x >= 0) {
	this->heroe->sprite.move(-5.f, 0.f);
  }
  if (this->heroe->sprite.getPosition().x <= 0) {
	this->heroe->sprite.setPosition(sf::Vector2f(1.f, static_cast<float> (this->gameManager->window->getSize().y) - this->heroe->sprite.getGlobalBounds().height));
  }
  if ((this->heroe->sprite.getPosition().x + this->heroe->sprite.getGlobalBounds().width) >= this->gameManager->window->getSize().x) {
	this->heroe->sprite.setPosition(sf::Vector2f((this->gameManager->window->getSize().x - this->heroe->sprite.getGlobalBounds().width),
	  static_cast<float> (this->gameManager->window->getSize().y) - this->heroe->sprite.getGlobalBounds().height));
  }
  this->moveRight = false;
  this->moveLeft = false;
}

Gameplay::Gameplay(std::shared_ptr<Gamemanager>& gameMan) : gameManager(gameMan) {
  this->heroe = std::make_unique<Spaceship>(this->gameManager);
  this->initVars();
}

Gameplay::~Gameplay() { }

void Gameplay::run() {
  this->update();
  this->render();
}

void Gameplay::poll() {
  sf::Event ev;
  while (this->gameManager->window->pollEvent(ev)) {
	switch (ev.type) {
	case sf::Event::Closed:
	  this->gameManager->window->close();
	  break;
	case sf::Event::KeyPressed:
	  if (ev.key.code == sf::Keyboard::Escape) {
		this->gameManager->window->close();
	  }
	  if (ev.key.code == sf::Keyboard::Z) {
		this->moveLeft = true;
	  }
	  if (ev.key.code == sf::Keyboard::X) {
		this->moveRight = true;
	  }
	}
  }
}

void Gameplay::update() {
  this->poll();
  this->updateHeroe();
}

void Gameplay::render() {
  this->gameManager->window->clear();
  this->gameManager->window->draw(this->heroe->sprite);
  this->gameManager->window->display();
}


