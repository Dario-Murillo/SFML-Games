#include "Gameplay.h"

Gameplay::Gameplay(std::shared_ptr<GameManager> gameMan) : gameManager(gameMan) {}

Gameplay::~Gameplay() { }


void Gameplay::initVar() {
  this->points = 0;
  this->enemySpawnTimerMax = 10.f;
  this->enemySpawnTimer = this->enemySpawnTimerMax;
  this->maxEnemies = 5;
  this->mouseHeld = false;
  this->health = 10;
  this->endGame = false;
}


void Gameplay::init() {
  this->initVar();
  this->initEnemies();
  this->initFonts();
  this->initText();
}


void Gameplay::initEnemies() {
  // this->enemie.setPosition(200, 300);
  /*this->enemie.setSize(sf::Vector2f(100.f, 100.f));
  this->enemie.setScale(sf::Vector2f(.5, .5));
  this->enemie.setFillColor(sf::Color::Magenta);*/
  int type = rand() % 5;
  this->enemie = Enemie(type);
}

void Gameplay::initFonts() {
  if (!this->font.loadFromFile("Fonts/ARCADECLASSIC.ttf")) {
	std::cerr << "Failed to load font" << std::endl;
  }
}

void Gameplay::initText() {
  this->uiText.setFont(this->font);
  this->uiText.setCharacterSize(30);
  this->uiText.setFillColor(sf::Color::White);
  this->uiText.setString("NULL");
}


void Gameplay::input() {
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

void Gameplay::update(sf::Time DeltaTime) {
  this->input();

  if (this->endGame == false) {
	this->updateMousePositions();
	this->updateEnemies();
	this->updateText();
  }
  if (this->health <= 0) {
	this->endGame = true;
	this->gameManager->state->push(std::make_unique<Endscreen>(this->gameManager), true);
  }
}

void Gameplay::render() {
  // Clears old frame
  this->gameManager->window->clear();
  //this->window->draw(this->enemie);

  // Draw game
  this->renderEnemies(*this->gameManager->window);
  this->renderText(*this->gameManager->window);
  this->gameManager->window->display();
}

void Gameplay::updateMousePositions() {
  this->mousePosition = sf::Mouse::getPosition(*this->gameManager->window);
  this->mousePositionView = this->gameManager->window->mapPixelToCoords(this->mousePosition);
}

void Gameplay::updateText() {
  std::stringstream buffer;
  buffer << "Points " << this->points << "\n" << " Health " << this->health;
  this->uiText.setString(buffer.str());
}

void Gameplay::updateEnemies() {
  /* Updates the enemy spawn timer and spawns new enemies if the max has not been reached*/
  if (this->enemies.size() < this->maxEnemies) {
	if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
	  this->spawnEnemy();
	  this->enemySpawnTimer = 0.f;
	}
	else {
	  this->enemySpawnTimer += 1.f;
	}
  }

  // Check if enemy is outside of the screen
  for (int i = 0; i < this->enemies.size(); i++) {
	this->enemies[i].figure.move(0.f, 2.f);
	// If the enemy is out of range (bottom of the screen) we delet it 
	if (this->enemies[i].figure.getPosition().y > this->gameManager->window->getSize().y) {
	  this->enemies.erase(this->enemies.begin() + i);
	  this->health -= 1;
	  // std::cout << "Health: " << this->health << std::endl;
	}
  }


  // Check if the enemy was clicked
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
	if (this->mouseHeld == false) {
	  this->mouseHeld = true;
	  bool toDelete = false;
	  // If the enemy was clicked we delete it
	  for (size_t i = 0; i < this->enemies.size() && toDelete == false; i++) {

		if (this->enemies[i].figure.getGlobalBounds().contains(this->mousePositionView)) {
		  this->points += this->enemies[i].getValuePoints();
		  toDelete = true;
		  this->enemies.erase(this->enemies.begin() + i);

		}
	  }
	}
  }
  else {
	this->mouseHeld = false;
  }
}

void Gameplay::spawnEnemy() {
  // Randomize enemy type
  int type = rand() % 5;
  this->enemie = Enemie(type);
  // Sets the enemy in a random position
  this->enemie.figure.setPosition(
	static_cast<float>(rand() % static_cast<int>(this->gameManager->window->getSize().x - this->enemie.figure.getSize().x)),
	0.f
  );

  // Spawn the enemy and store it
  this->enemies.push_back(this->enemie);
}

void Gameplay::renderEnemies(sf::RenderTarget& target) {
  for (auto& e : this->enemies) {
	target.draw(e.figure);
  }
}

void Gameplay::renderText(sf::RenderTarget& target) const {
  target.draw(this->uiText);
}


void Gameplay::Pause() {
}

void Gameplay::Start() {
}
