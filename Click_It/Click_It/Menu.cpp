#include "Menu.h"

Menu::Menu(std::shared_ptr<GameManager>& gameMan) : gameManager(gameMan) {}

Menu::~Menu() {}

void Menu::init() {
  this->gameManager->assets->addFont(MAIN_FONT, "Fonts/ARCADECLASSIC.ttf");
  this->gameTitle.setFont(this->gameManager->assets->getFont(MAIN_FONT));
  this->gameTitle.setString("Start");
  this->gameTitle.setCharacterSize(50);
  this->gameTitle.setOrigin(this->gameTitle.getGlobalBounds().width / 2, this->gameTitle.getGlobalBounds().height / 2);
  this->gameTitle.setPosition(
	static_cast<float> (this->gameManager->window->getSize().x / 2),
	static_cast<float> (this->gameManager->window->getSize().y / 2));
}

void Menu::input() {
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
	  break;
	}
  }
}

void Menu::update(sf::Time DeltaTime) {
  this->input();
  updateMousePositions();

  // If we hover over the star button we turn it red
  if (this->gameTitle.getGlobalBounds().contains(this->mousePositionView)) {
	this->gameTitle.setFillColor(sf::Color::Red);
  }
  else {
	this->gameTitle.setFillColor(sf::Color::White);
  }


  // If the button is pressed and it was in the start position it means we need to star the game
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
	if (this->gameTitle.getGlobalBounds().contains(this->mousePositionView)) {
	  // TODO:
	  // Change screens
	  this->gameManager->state->push(std::make_unique<Gameplay>(this->gameManager), true);
	}
  }

}

void Menu::render() {
  this->gameManager->window->clear();
  this->gameManager->window->draw(this->gameTitle);
  this->gameManager->window->display();
}

void Menu::updateMousePositions() {
  this->mousePosition = sf::Mouse::getPosition(*this->gameManager->window);
  this->mousePositionView = this->gameManager->window->mapPixelToCoords(this->mousePosition);
  /*std::cout << "X: " << this->mousePosition.x << std::endl;
  std::cout << "Y: " << this->mousePosition.y << std::endl;*/
}
