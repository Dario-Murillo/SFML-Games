#include "Menu.h"

Menu::Menu(std::shared_ptr<Gamemanager> gameMan) : gameManager(gameMan) {}

Menu::~Menu() {}

void Menu::run() {
  this->update();
  this->render();
}

void Menu::poll() {
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

void Menu::update() {
  this->poll();
}

void Menu::render() {
  this->gameManager->window->clear();
  this->gameManager->window->display();
}
