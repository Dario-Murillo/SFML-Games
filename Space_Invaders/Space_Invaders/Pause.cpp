#include "Pause.h"

Pause::Pause(std::shared_ptr<Gamemanager>& gameMan) : gameManager(gameMan) {
  this->initFonts();
  this->initText();
}

Pause::~Pause() {}

void Pause::run() {
  this->update();
  this->render();
}

void Pause::poll() {
  sf::Event ev;
  while (this->gameManager->window->pollEvent(ev)) {
	switch (ev.type) {
	case sf::Event::Closed:
	  this->gameManager->window->close();
	  break;
	}
  }
}

void Pause::update() {
  this->poll();
  this->updateMousePositions();
  this->updateText();
}

void Pause::render() {
  this->gameManager->window->clear();
  this->gameManager->window->draw(this->continueTitle);
  this->gameManager->window->draw(this->menuTitle);
  this->gameManager->window->draw(this->exitTitle);
  this->gameManager->window->display();

}

void Pause::updateMousePositions() {
  this->mousePosition = sf::Mouse::getPosition(*this->gameManager->window);
  this->mousePositionView = this->gameManager->window->mapPixelToCoords(this->mousePosition);
}

void Pause::updateText() {
  if (this->exitTitle.getGlobalBounds().contains(this->mousePositionView)) {
	this->exitTitle.setFillColor(sf::Color::Red);
  }
  else {
	this->exitTitle.setFillColor(sf::Color::White);
  }

  if (this->continueTitle.getGlobalBounds().contains(this->mousePositionView)) {
	this->continueTitle.setFillColor(sf::Color::Red);
  }
  else {
	this->continueTitle.setFillColor(sf::Color::White);
  }


  if (this->menuTitle.getGlobalBounds().contains(this->mousePositionView)) {
	this->menuTitle.setFillColor(sf::Color::Red);
  }
  else {
	this->menuTitle.setFillColor(sf::Color::White);
  }

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
	if (this->exitTitle.getGlobalBounds().contains(this->mousePositionView)) {
	  this->gameManager->window->close();
	}
	if (this->menuTitle.getGlobalBounds().contains(this->mousePositionView)) {
	  this->gameManager->screen_manager->setcurrentScreen(MENU);
	}
	if (this->continueTitle.getGlobalBounds().contains(this->mousePositionView)) {
	  this->gameManager->screen_manager->setcurrentScreen(GAMEPLAY);
	}
  }
}

void Pause::initFonts() {
  if (!this->font.loadFromFile("Fonts/ARCADECLASSIC.ttf")) {
	std::cerr << "Failed to load font" << std::endl;
  }
}

void Pause::initText() {
  this->continueTitle.setFont(this->font);
  this->continueTitle.setString("Continue");

  this->continueTitle.setCharacterSize(35);
  this->continueTitle.setOrigin(this->continueTitle.getGlobalBounds().width / 2, 0);
  this->continueTitle.setPosition(
	static_cast<float> (this->gameManager->window->getSize().x / 2),
	static_cast<float> (this->gameManager->window->getSize().y / 2) - 20.f);

  this->menuTitle.setFont(this->font);
  this->menuTitle.setString("Menu");
  this->menuTitle.setCharacterSize(35);
  this->menuTitle.setOrigin(this->menuTitle.getGlobalBounds().width / 2, this->menuTitle.getGlobalBounds().height / 2);
  this->menuTitle.setPosition(
	static_cast<float> (this->gameManager->window->getSize().x / 2),
	static_cast<float> (this->gameManager->window->getSize().y / 2) + 40.f);


  this->exitTitle.setFont(this->font);
  this->exitTitle.setString("Exit");
  this->exitTitle.setCharacterSize(35);
  this->exitTitle.setOrigin(this->exitTitle.getGlobalBounds().width / 2, this->exitTitle.getGlobalBounds().height / 2);
  this->exitTitle.setPosition(
	static_cast<float> (this->gameManager->window->getSize().x / 2),
	static_cast<float> (this->gameManager->window->getSize().y / 2) + 80.f);
}
