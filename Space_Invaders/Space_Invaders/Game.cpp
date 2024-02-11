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
  while (this->gameManager->window->isOpen()) {
    this->gameManager->screen_manager->getCurrentScreen()->run();
  }
}


