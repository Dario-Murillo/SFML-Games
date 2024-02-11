#include "Gameplay.h"

Gameplay::Gameplay(std::shared_ptr<Gamemanager>& gameMan) : gameManager(gameMan) {

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
	}
  }
}

void Gameplay::update() {
  this->poll();
}

void Gameplay::render() {
  this->gameManager->window->clear();
  this->gameManager->window->display();
}


