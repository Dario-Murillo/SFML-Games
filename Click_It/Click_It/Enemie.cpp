#include "Enemie.h"

int Enemie::getValuePoints() const {
  return this->valuePoints;
}

Enemie::Enemie() {
  this->valuePoints = 0;
}

Enemie::Enemie(int type) {
  switch (type) {
  case 0:
	this->figure.setSize(sf::Vector2f(20.f, 20.f));
	this->figure.setScale(sf::Vector2f(.5, .5));
	this->figure.setFillColor(sf::Color::Red);
	this->figure.setPosition(200, 300);
	this->valuePoints = 40;
	break;
  case 1:
	this->figure.setSize(sf::Vector2f(30.f, 30.f));
	this->figure.setFillColor(sf::Color::Blue);
	this->figure.setPosition(200, 300);
	this->figure.setScale(sf::Vector2f(.5, .5));
	this->valuePoints = 30;
	break;
  case 2:
	this->figure.setSize(sf::Vector2f(40.f, 40.f));
	this->figure.setFillColor(sf::Color::Yellow);
	this->figure.setPosition(200, 300);
	this->figure.setScale(sf::Vector2f(.5, .5));
	this->valuePoints = 20;
	break;
  case 3:
	this->figure.setSize(sf::Vector2f(60.f, 60.f));
	this->figure.setScale(sf::Vector2f(.5, .5));
	this->figure.setFillColor(sf::Color::Cyan);
	this->figure.setPosition(200, 300);
	this->valuePoints = 10;
	break;
  case 4:
	this->figure.setSize(sf::Vector2f(100.f, 100.f));
	this->figure.setFillColor(sf::Color::Magenta);
	this->figure.setPosition(200, 300);
	this->figure.setScale(sf::Vector2f(.5, .5));
	this->valuePoints = 5;
	break;
  default:
	this->figure.setSize(sf::Vector2f(100.f, 100.f));
	this->figure.setFillColor(sf::Color::Magenta);
	this->figure.setPosition(200, 300);
	this->figure.setScale(sf::Vector2f(.5, .5));
	this->valuePoints = 5;
	break;
  }
}

Enemie::~Enemie() {}
