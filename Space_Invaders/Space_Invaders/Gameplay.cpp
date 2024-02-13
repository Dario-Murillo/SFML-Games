#include "Gameplay.h"


void Gameplay::initVars() {
  this->point_count = 0;
  this->shootHeld = false;
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
  this->points.setOrigin(-20.f, 0.f);
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
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
	this->heroe->sprite.move(2.f, 0.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
	this->heroe->sprite.move(-2.f, 0.f);
  }
  if (this->heroe->sprite.getPosition().x <= 0) {
	this->heroe->sprite.setPosition(sf::Vector2f(1.f, static_cast<float> (this->gameManager->window->getSize().y) - this->heroe->sprite.getGlobalBounds().height));
  }
  if ((this->heroe->sprite.getPosition().x + this->heroe->sprite.getGlobalBounds().width) >= this->gameManager->window->getSize().x) {
	this->heroe->sprite.setPosition(sf::Vector2f((this->gameManager->window->getSize().x - this->heroe->sprite.getGlobalBounds().width),
	  static_cast<float> (this->gameManager->window->getSize().y) - this->heroe->sprite.getGlobalBounds().height));
  }
}

void Gameplay::spawnBullet() {
  this->bullet.setPosition(sf::Vector2f(
	this->heroe->sprite.getPosition().x + (this->heroe->sprite.getGlobalBounds().width / 2),
	this->gameManager->window->getSize().y - this->heroe->sprite.getGlobalBounds().height));


  this->bullets.push_back(this->bullet);
}

void Gameplay::spawnEnemieBullet() {
  int choose = rand() % this->enemies.size();;
  // If the enemie is not null
  if (this->enemies[choose] != nullptr && this->enemies[choose]->already_shoot == false) {
	this->enemies[choose]->bullet.setPosition(sf::Vector2f(
	  this->enemies[choose]->sprite.getPosition().x + (this->enemies[choose]->sprite.getGlobalBounds().width / 2),
	  0.f));
	this->enemies[choose]->already_shoot = true;
  }
}

void Gameplay::updateBullets() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
	if (this->shootHeld == false) {
	  this->shootHeld = true;
  	  this->spawnBullet();
	}
  } else {
	this->shootHeld = false;
  }

  // If the bullet is out of the screen we delete it
  for (size_t i = 0; i < this->bullets.size(); i++) {
	this->bullets[i].move(0.f, -2.f);
	if (this->bullets[i].getPosition().y <= 0) {
	  this->bullets.erase(this->bullets.begin() + i);
	}
  }

  for (size_t i = 0; i < this->enemies.size(); i++) {
	for (size_t k = 0; k < this->bullets.size(); k++) {
	  if (enemies[i]->sprite.getGlobalBounds().intersects(this->bullets[k].getGlobalBounds())) {
		this->point_count += this->enemies[i]->valuePoints;
		this->enemies.erase(this->enemies.begin() + i);
		this->bullets.erase(this->bullets.begin() + k);
	  }
	}
  }
}

void Gameplay::updateEnemieBullets() {
  this->spawnEnemieBullet();
  for (size_t i = 0; i < this->enemies.size(); i++) {
	if (enemies[i] != nullptr) {
	  this->enemies[i]->bullet.move(0.f, 2.f);
	}
  }

  // If the bullet is offscreen we delete it
  for (size_t i = 0; i < this->enemies.size(); i++) {
	if (enemies[i] != nullptr) {
	  if (this->enemies[i]->bullet.getPosition().y >= this->gameManager->window->getSize().y) {
		this->enemies[i]->can_move = false;
		this->enemies[i]->already_shoot = false;
	  }
	}
  }
}

void Gameplay::updateText() {
  std::stringstream buff;
  buff << "Points " << this->point_count;
  this->points.setString(buff.str());
}

void Gameplay::updateEnemies() {
  // Check if a bullet hit an enemie

}

void Gameplay::drawBullets(sf::RenderTarget& target) {
  for (auto& bullet : this->bullets) {
	target.draw(bullet);
  }
}

void Gameplay::drawText(sf::RenderTarget& target) {
  target.draw(this->points);
}

void Gameplay::drawEnemies(sf::RenderTarget& target) {
  for (auto& enemie : this->enemies ) {
	target.draw(enemie->sprite);
  }
}

void Gameplay::drawEnemieBullets(sf::RenderTarget& target) {
  for (auto &eBullet : this->enemies) {
	target.draw(eBullet->bullet);
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
		break;
	  }
	}
  }
}

void Gameplay::update() {
  this->poll();
  this->updateHeroe();
  this->updateEnemies();
  this->updateBullets();
  this->updateText();
  // this->updateEnemieBullets();
}

void Gameplay::render() {
  this->gameManager->window->clear();
  this->gameManager->window->draw(this->heroe->sprite);
  this->drawEnemies(*this->gameManager->window);
  this->drawBullets(*this->gameManager->window);
  this->drawText(*this->gameManager->window);
  // this->drawEnemieBullets(*this->gameManager->window);
  this->gameManager->window->display();
}


