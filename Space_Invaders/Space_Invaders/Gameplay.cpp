#include "Gameplay.h"

constexpr float ENEMIE_WIDTH = 28.9;

void Gameplay::initVars() {
  this->point_count = 0;
  this->shootHeld = false;
  this->spawn_enemie_bullet = false;
  this->enemie_x_speed = 2;
  this->enemie_y_speed = 0;
}

void Gameplay::initBullet() {
  this->bullet.setScale(1.f, 1.f);
  this->bullet.setSize(sf::Vector2f(3.f, 15.f));
  this->bullet.setFillColor(sf::Color::Green);

  this->enemie_bullet.setScale(1.f, 1.f);
  this->enemie_bullet.setSize(sf::Vector2f(3.f, 15.f));
  this->enemie_bullet.setFillColor(sf::Color::Red);
  this->time_since_last_bullet = sf::Time::Zero;
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

  this->lives.setFont(this->font);
  this->lives.setCharacterSize(30);
  this->lives.setFillColor(sf::Color::White);
  this->lives.setString("Lives: ");
  this->lives.setPosition(this->gameManager->window->getSize().x - this->lives.getGlobalBounds().width - 20, 0.f);
}

void Gameplay::initEnemies() {
  int type = 1;
  float xPos = ENEMIE_WIDTH * 2;
  float yPos = this->points.getGlobalBounds().height + 40;
  for (size_t cols = 1; cols <= 8; cols++) {
	if (cols <= 2) {
	  type = 1;
	}
	if (cols >= 3 && cols <= 5) {
	  type = 2;
	}
	if (cols >= 6) {
	  type = 3;
	}
	do {
	  this->enemies.push_back(std::make_unique<Enemie>(type, this->gameManager, xPos, yPos));
	  xPos += ENEMIE_WIDTH;
	} while ((xPos + ENEMIE_WIDTH)  < (this->gameManager->window->getSize().x) - (ENEMIE_WIDTH));
	yPos += this->enemies[cols]->sprite.getGlobalBounds().height;
	xPos = ENEMIE_WIDTH * 2;
  }
  this->originalSize = this->enemies.size();
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
  // We choose a random enemie to "shoot" the bullet (we only need his coordinates to make it seem like he shot it)
  int choose = rand() % this->enemies.size();
  this->enemie_bullet.setPosition(sf::Vector2f(
	this->enemies[choose]->sprite.getPosition().x + (this->enemies[choose]->sprite.getGlobalBounds().width / 2),
	this->enemies[choose]->sprite.getPosition().y + (this->enemies[choose]->sprite.getGlobalBounds().height)));

  this->enemie_bullets.push_back(this->enemie_bullet);
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

  bool deleted = false;
  for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
	for (size_t k = 0; k < this->bullets.size() && deleted == false; k++) {
	  if (enemies[i]->sprite.getGlobalBounds().intersects(this->bullets[k].getGlobalBounds())) {
		this->point_count += this->enemies[i]->valuePoints;
		this->enemies.erase(this->enemies.begin() + i);
		this->bullets.erase(this->bullets.begin() + k);
		deleted = true;
	  }
	}
  }
}

void Gameplay::updateEnemieBullets() {
  if (this->spawn_enemie_bullet) {
	this->spawnEnemieBullet();
	this->spawnEnemieBullet();
	this->spawnEnemieBullet();
	this->spawn_enemie_bullet = false;
  }
  for (size_t i = 0; i < this->enemie_bullets.size(); i++) {
	this->enemie_bullets[i].move(0.f, 5.f);
	if (this->enemie_bullets[i].getPosition().y > this->gameManager->window->getSize().y) {
	  this->enemie_bullets.erase(this->enemie_bullets.begin() + i);
	}
  }

  // Then we need to check for collisions with the heroe
  for (size_t i = 0; i < this->enemie_bullets.size(); i++) {
	if (this->enemie_bullets[i].getGlobalBounds().intersects(this->heroe->sprite.getGlobalBounds())) {
	  this->enemie_bullets.erase(this->enemie_bullets.begin() + i);
	  this->heroe->subLives();
	}
  }
}

void Gameplay::updateText() {
  std::stringstream buff;
  buff << "Points " << this->point_count;
  this->points.setString(buff.str());

  std::stringstream buff2;
  buff2 << "Lives " << this->heroe->getLives();
  this->lives.setString(buff2.str());
  
}

void Gameplay::updateEnemies() {

  this->enemie_y_speed = 0;
  // If there is 1/4 or less of the original enemies we speed up 
  if (this->enemies.size() <= this->originalSize / 2) {
	this->enemie_x_speed = this->enemie_x_speed * 1.1f;
  }
  for (size_t i = 0; i < this->enemies.size(); i++) {

	if (this->enemies[i]->sprite.getPosition().x <= 0) {
	  this->enemie_x_speed = 2.f;
	  this->enemie_y_speed = 5.f;
	}
	if (this->enemies[i]->sprite.getPosition().x + this->enemies[i]->sprite.getGlobalBounds().width >= this->gameManager->window->getSize().x) {
	  this->enemie_x_speed = -2.f;
	  this->enemie_y_speed = 5.f;
	}


  }
  // Check if any enemy is off the screen or if it is in the last line
  for (size_t i = 0; i < this->enemies.size(); i++) {
	this->enemies[i]->sprite.move(this->enemie_x_speed, this->enemie_y_speed);
	if (this->enemies[i]->sprite.getPosition().y + this->enemies[i]->sprite.getGlobalBounds().height > this->gameManager->window->getSize().y
	  || this->enemies[i]->sprite.getGlobalBounds().intersects(this->heroe->sprite.getGlobalBounds()) || this->heroe->getLives() <= 0) {
	  // Here you lose
	  this->gameManager->screen_manager->addScreen(ENDSCREEN, std::make_unique<Endscreen>(this->gameManager, "You Lost"));
	}
  }

  // If the enemie array is empty the player won
  if (this->enemies.size() == 0) {
	this->gameManager->screen_manager->addScreen(ENDSCREEN, std::make_unique<Endscreen>(this->gameManager, "You Won"));
  }

}

void Gameplay::drawBullets(sf::RenderTarget& target) {
  for (auto& bullet : this->bullets) {
	target.draw(bullet);
  }
}

void Gameplay::drawText(sf::RenderTarget& target) const {
  target.draw(this->points);
  target.draw(this->lives);
}

void Gameplay::drawEnemies(sf::RenderTarget& target) {
  for (auto& enemie : this->enemies ) {
	target.draw(enemie->sprite);
  }
}

void Gameplay::drawEnemieBullets(sf::RenderTarget& target) {
  for (auto &eBullet : this->enemie_bullets) {
	target.draw(eBullet);
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
	this->time_since_last_bullet = this->enemie_bullet_clock.getElapsedTime();
	if (this->time_since_last_bullet > sf::seconds(5.f)) {
	  this->spawn_enemie_bullet = true;
	  this->enemie_bullet_clock.restart();
	}

	switch (ev.type) {
	case sf::Event::Closed:
	  this->gameManager->window->close();
	  break;
	case sf::Event::KeyPressed:
	  if (ev.key.code == sf::Keyboard::Escape) {
		this->gameManager->screen_manager->setcurrentScreen(PAUSE);
		this->enemie_bullet_clock.restart();
		this->time_since_last_bullet = sf::seconds(0.f);
		this->spawn_enemie_bullet = false;
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
  this->updateEnemieBullets();
}

void Gameplay::render() {
  this->gameManager->window->clear();
  this->gameManager->window->draw(this->heroe->sprite);
  this->drawEnemies(*this->gameManager->window);
  this->drawBullets(*this->gameManager->window);
  this->drawText(*this->gameManager->window);
  this->drawEnemieBullets(*this->gameManager->window);
  this->gameManager->window->display();
}
