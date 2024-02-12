#include "Gameplay.h"


void Gameplay::initVars() {
  this->moveLeft = false;
  this->moveRight = false;
  this->shoot = false;
  this->point_count = 0;
}

void Gameplay::initBullet() {
  this->bullet.setScale(1.f, 1.f);
  this->bullet.setSize(sf::Vector2f(3.f, 15.f));
  this->bullet.setFillColor(sf::Color::Green);
}

void Gameplay::initText() {
  if (!this->font.loadFromFile("Fonts/ARCADECLASSIC.ttf")) {
	std::cerr << "Failed to load font" << std::endl;
  }
  this->points.setFont(this->font);
  this->points.setCharacterSize(30);
  this->points.setFillColor(sf::Color::White);
  this->points.setString("Points: ");
}

void Gameplay::initEnemies() {
  int type = 1;
  float xPos = 10;
  float yPos = this->points.getGlobalBounds().height + 20;
  for (size_t cols = 1; cols <= 5; cols++) {
	if (cols == 2 || cols == 3) {
	  type = 2;
	}
	if (cols == 4 || cols == 5) {
	  type = 3;
	}
	do {
	  this->enemies.push_back(std::make_unique<Enemie>(type, this->gameManager, xPos, yPos));
	  xPos += this->enemies[0]->sprite.getGlobalBounds().width;

	} while ((xPos + this->enemies[0]->sprite.getGlobalBounds().width)  < this->gameManager->window->getSize().x);
	yPos += this->enemies[cols]->sprite.getGlobalBounds().height;
	xPos = 10;
  }
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
  if (this->shoot) {
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
	}
  }

}

void Gameplay::updateText() {
  std::stringstream buff;
  buff << "Points " << this->point_count;
  this->points.setString(buff.str());
}

void Gameplay::updateEnemies() {
  for (size_t i = 0; i < this->enemies.size(); i++) {
	for (size_t k = 0; k < this->bullets.size(); k++) {
	  if (enemies[i]->sprite.getGlobalBounds().intersects(this->bullets[k].getGlobalBounds())) {
		this->enemies.erase(this->enemies.begin() + i);
		this->bullets.erase(this->bullets.begin() + k);
	  }
	}
  }
}

void Gameplay::drawBullets() {
  for (size_t i = 0; i < this->bullets.size(); i++) {
	this->gameManager->window->draw(this->bullets[i]);
  }
}

void Gameplay::drawText() {
  this->gameManager->window->draw(this->points);
}

void Gameplay::drawEnemies() {
  for (size_t i = 0; i < this->enemies.size(); i++) {
	this->gameManager->window->draw(this->enemies[i]->sprite);
  }
}

Gameplay::Gameplay(std::shared_ptr<Gamemanager>& gameMan) : gameManager(gameMan) {
  this->heroe = std::make_unique<Spaceship>(this->gameManager);
  this->initVars();
  this->initBullet();
  this->initText();
  this->initEnemies();
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
  this->updateText();
  this->updateEnemies();
}

void Gameplay::render() {
  this->gameManager->window->clear();
  this->gameManager->window->draw(this->heroe->sprite);
  this->drawBullets();
  this->drawText();
  this->drawEnemies();
  this->gameManager->window->display();
}


