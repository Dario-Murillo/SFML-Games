#include "Game.h"
#include "Gameplay.h"
#include "Menu.h"

void Game::initWindow() {
  this->videoMode.height = 600;
  this->videoMode.width = 800;
  this->gameManager->window->create(this->videoMode, "VideoGame", sf::Style::Titlebar | sf::Style::Close);
  this->gameManager->window->setFramerateLimit(60);
}

Game::Game() : gameManager(std::make_shared<GameManager>()) {
  initWindow();
  // Push menu state onto the stack (menu is the first state)
  this->gameManager->state->push(std::make_unique<Menu>(this->gameManager));
}

Game::~Game() { }

void Game::Start() {

  sf::Clock clock;
  sf::Time time_since_last_frame = sf::Time::Zero;

  while (this->gameManager->window->isOpen()) {

	time_since_last_frame += clock.restart();

	while (time_since_last_frame > sf::seconds(1.f / 60.f)) {
	  time_since_last_frame -= sf::seconds(1.f / 60.f);

	  this->gameManager->state->process();
	  this->gameManager->state->getCurrent()->update(sf::seconds(1.f / 60.f));
	  this->gameManager->state->getCurrent()->render();
	}
  }
}
