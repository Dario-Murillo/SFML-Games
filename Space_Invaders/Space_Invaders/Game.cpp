#include "Game.h"
#include "Menu.h"

Game::Game() : gameManager(std::make_shared<Gamemanager>()) {
  this->initWindow();
}

Game::~Game() { }

void Game::initWindow() {
  this->viewmode.width = 600;
  this->viewmode.height = 800;
  this->gameManager->window->create(this->viewmode, "Space Invaders", sf::Style::Titlebar | sf::Style::Close);
  this->gameManager->window->setFramerateLimit(60);
}

void Game::start() {
  this->gameManager->screen_manager->addScreen(MENU, std::make_unique<Menu>(this->gameManager));

  sf::Clock clock;
  sf::Time time_since_last_frame = sf::Time::Zero;

  while (this->gameManager->window->isOpen()) {
    time_since_last_frame += clock.restart();

    while (time_since_last_frame > sf::seconds(1.f / 60.f)) {
      time_since_last_frame -= sf::seconds(1.f / 60.f);
      this->gameManager->screen_manager->getCurrentScreen()->run();
    }
  }
}

