#include "Gameplay.h"


void Gameplay::initVars() {
  this->moveLeft = false;
  this->moveRight = false;
  this->shoot = false;
}

void Gameplay::initBullet() {
  this->bullet.setScale(1.f, 1.f);
  this->bullet.setSize(sf::Vector2f(3.f, 15.f));
  this->bullet.setFillColor(sf::Color::Green);
}

void Gameplay::updateHeroe() {
  if (this->moveLeft) {
	this->heroe->sprite.move(5.f, 0.f);
  }
  if (this->moveRight && this->heroe->sprite.getPosition().x >= 0) {
	this->heroe->sprite.move(-5.f, 0.f);
  }
  if (this->heroe->sprite.getPosition().x <= 0) {
	this->heroe->sprite.setPosition(sf::Vector2f(1.f, static_cast<float> (this->gameManager->window->getSize().y) - this->heroe->sprite.getGlobalBounds().height));
  }
  if ((this->heroe->sprite.getPosition().x + this->heroe->sprite.getGlobalBounds().width) >= this->gameManager->window->getSize().x) {
	this->heroe->sprite.setPosition(sf::Vector2f((this->gameManager->window->getSize().x - this->heroe->sprite.getGlobalBounds().width),
	  static_cast<float> (this->gameManager->window->getSize().y) - this->heroe->sprite.getGlobalBounds().height));
  }
  this->moveRight = false;
  this->moveLeft = false;
}

void Gameplay::spawnBullet() {
  this->bullet.setPosition(sf::Vector2f(
	this->heroe->sprite.getPosition().x + (this->heroe->sprite.getGlobalBounds().width / 2),
	this->gameManager->window->getSize().y - this->heroe->sprite.getGlobalBounds().height));


  this->bullets.push_back(this->bullet);
}

void Gameplay::updateBullets() {
  if (shoot) {
	this->spawnBullet();
  }
  this->shoot = false;
  for (size_t i = 0; i < this->bullets.size(); i++) {
	this->bullets[i].move(0.f, -2.f);
  }

  // If the bullet is off the screen we delete it
  for (size_t i = 0; i < this->bullets.size(); i++) {
	if (this->bullets[i].getPosition().y <= 0) {
	  this->bullets.erase(this->bullets.begin() + i);
	  std::cout << "deleted" << std::endl;
	}
  }

}

void Gameplay::drawBullets() {
  for (size_t i = 0; i < this->bullets.size(); i++) {
	this->gameManager->window->draw(this->bullets[i]);
  }
}

Gameplay::Gameplay(std::shared_ptr<Gamemanager>& gameMan) : gameManager(gameMan) {
  this->heroe = std::make_unique<Spaceship>(this->gameManager);
  this->initVars();
  this->initBullet();
}

Gameplay::~Gameplay() { }

void Gameplay::run() {
  this->update();
  this->render();
}

void Gameplay::poll() {
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
	  if (ev.key.code == sf::Keyboard::Z) {
		this->moveLeft = true;
	  }
	  if (ev.key.code == sf::Keyboard::X) {
		this->moveRight = true;
	  }
	  if (ev.key.code == sf::Keyboard::Space) {
		this->shoot = true;
	  }
	  break;
	}
  }
}

void Gameplay::update() {
  this->poll();
  this->updateHeroe();
  this->updateBullets();
}

void Gameplay::render() {
  this->gameManager->window->clear();
  this->gameManager->window->draw(this->heroe->sprite);
  this->drawBullets();
  this->gameManager->window->display();
}


