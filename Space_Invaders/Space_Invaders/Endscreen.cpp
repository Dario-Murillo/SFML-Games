#include "Endscreen.h"

void Endscreen::initFonts() {
  if (!this->font.loadFromFile("Fonts/ARCADECLASSIC.ttf")) {
	std::cerr << "Failed to load font" << std::endl;
  }
}

void Endscreen::initText() {
  this->mainTitle.setFont(this->font);
  this->mainTitle.setString(this->mainText);

  this->mainTitle.setCharacterSize(50);
  this->mainTitle.setOrigin(this->mainTitle.getGlobalBounds().width / 2, 0);
  this->mainTitle.setPosition(
	static_cast<float> (this->gameManager->window->getSize().x / 2),
	static_cast<float> (45));

  this->menuTitle.setFont(this->font);
  this->menuTitle.setString("Menu");
  this->menuTitle.setCharacterSize(35);
  this->menuTitle.setOrigin(this->menuTitle.getGlobalBounds().width / 2, this->menuTitle.getGlobalBounds().height / 2);
  this->menuTitle.setPosition(
	static_cast<float> (this->gameManager->window->getSize().x / 2),
	static_cast<float> (this->gameManager->window->getSize().y / 2) - 40);


  this->exitTitle.setFont(this->font);
  this->exitTitle.setString("Exit");
  this->exitTitle.setCharacterSize(35);
  this->exitTitle.setOrigin(this->exitTitle.getGlobalBounds().width / 2, this->exitTitle.getGlobalBounds().height / 2);
  this->exitTitle.setPosition(
	static_cast<float> (this->gameManager->window->getSize().x / 2),
	static_cast<float> (this->gameManager->window->getSize().y / 2) + 80.f);

}

void Endscreen::updateMousePositions() {
  this->mousePosition = sf::Mouse::getPosition(*this->gameManager->window);
  this->mousePositionView = this->gameManager->window->mapPixelToCoords(this->mousePosition);
}

void Endscreen::updateText() {
  if (this->exitTitle.getGlobalBounds().contains(this->mousePositionView)) {
	this->exitTitle.setFillColor(sf::Color::Red);
  }
  else {
	this->exitTitle.setFillColor(sf::Color::White);
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

  }
}

void Endscreen::drawText(sf::RenderTarget& target) {
  target.draw(this->mainTitle);
  target.draw(this->menuTitle);
  target.draw(this->exitTitle);
}

Endscreen::Endscreen(std::shared_ptr<Gamemanager> gameMan, std::string mainText) : gameManager(gameMan), mainText(mainText) {
  this->initFonts();
  this->initText();
}

Endscreen::~Endscreen() { }

void Endscreen::run() {
  this->update();
  this->render();
}

void Endscreen::poll() {
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

void Endscreen::update() {
  this->poll();
  this->updateMousePositions();
  this->updateText();
}

void Endscreen::render() {
  this->gameManager->window->clear();
  this->drawText(*this->gameManager->window);
  this->gameManager->window->display();
}

