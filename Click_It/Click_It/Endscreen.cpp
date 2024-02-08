#include "Endscreen.h"

Endscreen::Endscreen(std::shared_ptr<GameManager> gameMan) : gameManager(gameMan) { }

Endscreen::~Endscreen() { }

void Endscreen::init() {
  this->endTitle.setFont(this->gameManager->assets->getFont(MAIN_FONT));
  std::stringstream buff;
  buff << "Game Over... " << "\n" << "Press esc to exit";
  this->endTitle.setString(buff.str());
  this->endTitle.setCharacterSize(50);
  this->endTitle.setOrigin(this->endTitle.getGlobalBounds().width / 2, this->endTitle.getGlobalBounds().height / 2);
  this->endTitle.setPosition(
	static_cast<float> (this->gameManager->window->getSize().x / 2),
	static_cast<float> (this->gameManager->window->getSize().y / 2));
}

void Endscreen::input() {
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

void Endscreen::update(sf::Time DeltaTime) {
  this->input();
}

void Endscreen::render() {
  this->gameManager->window->clear();
  this->gameManager->window->draw(this->endTitle);
  this->gameManager->window->display();
}

