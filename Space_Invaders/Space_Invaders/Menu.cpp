#include "Menu.h"

void Menu::initFonts() {
  if (!this->font.loadFromFile("Fonts/ARCADECLASSIC.ttf")) {
	std::cerr << "Failed to load font" << std::endl;
  }
}

void Menu::initText() {
  this->mainTitle.setFont(this->font);
  this->mainTitle.setString("Space Invaders");

  this->mainTitle.setCharacterSize(50);
  this->mainTitle.setOrigin(this->mainTitle.getGlobalBounds().width / 2, 0);
  this->mainTitle.setPosition(
	static_cast<float> (this->gameManager->window->getSize().x / 2),
	static_cast<float> (45));

  this->playTitle.setFont(this->font);
  this->playTitle.setString("Play");
  this->playTitle.setCharacterSize(35);
  this->playTitle.setOrigin(this->playTitle.getGlobalBounds().width / 2, this->playTitle.getGlobalBounds().height / 2);
  this->playTitle.setPosition(
	static_cast<float> (this->gameManager->window->getSize().x / 2),
	static_cast<float> (this->gameManager->window->getSize().y / 2));


  this->exitTitle.setFont(this->font);
  this->exitTitle.setString("Exit");
  this->exitTitle.setCharacterSize(35);
  this->exitTitle.setOrigin(this->exitTitle.getGlobalBounds().width / 2, this->exitTitle.getGlobalBounds().height / 2);
  this->exitTitle.setPosition(
	static_cast<float> (this->gameManager->window->getSize().x / 2),
	static_cast<float> (this->gameManager->window->getSize().y / 2) + 80.f);


}

void Menu::updateMousePositions() {
  this->mousePosition = sf::Mouse::getPosition(*this->gameManager->window);
  this->mousePositionView = this->gameManager->window->mapPixelToCoords(this->mousePosition);
}

void Menu::updateText() {
  if (this->exitTitle.getGlobalBounds().contains(this->mousePositionView)) {
	this->exitTitle.setFillColor(sf::Color::Red);
  } else {
	this->exitTitle.setFillColor(sf::Color::White);
  }

  if (this->playTitle.getGlobalBounds().contains(this->mousePositionView)) {
	this->playTitle.setFillColor(sf::Color::Red);
  } else {
	this->playTitle.setFillColor(sf::Color::White);
  }

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
	if (this->exitTitle.getGlobalBounds().contains(this->mousePositionView)) {
	  this->gameManager->window->close();
	}
	if (this->playTitle.getGlobalBounds().contains(this->mousePositionView)) {
	  this->gameManager->screen_manager->addScreen(GAMEPLAY, std::make_unique<Gameplay>(this->gameManager));
	}
  }
}

Menu::Menu(std::shared_ptr<Gamemanager>& gameMan) : gameManager(gameMan) {
  this->initFonts();
  this->initText();
}

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
  this->updateMousePositions();
  this->updateText();
}

void Menu::render() {
  this->gameManager->window->clear();
  this->gameManager->window->draw(this->mainTitle);
  this->gameManager->window->draw(this->playTitle);
  this->gameManager->window->draw(this->exitTitle);
  this->gameManager->window->display();
}
