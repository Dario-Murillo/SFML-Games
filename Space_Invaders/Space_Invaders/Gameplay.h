#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <sstream>
#include "Enemie.h"
#include "Game.h"
#include "Spaceship.h"

class Gameplay : public Screen {

private:
  // Shared pointer
  std::shared_ptr<Gamemanager>& gameManager;
  // Heroe
  std::unique_ptr<Spaceship> heroe;

  // Bullets
  std::vector<sf::RectangleShape> bullets;
  sf::RectangleShape bullet;

  // Boolean movement function
  bool moveLeft;
  bool moveRight;
  bool shoot;

  // Text and Font
  sf::Font font;
  sf::Text points;

  // Game Points
  int point_count;

  // Enemies
  std::vector<std::unique_ptr<Enemie>> enemies;

  // Init functions
  void initVars();
  void initBullet();
  void initText();
  void initEnemies();

  // Update functions
  void updateHeroe();
  void spawnBullet();
  void spawnEnemieBullet();
  void updateBullets();
  void updateEnemieBullets();
  void updateText();
  void updateEnemies();

  // Draw functions
  void drawBullets();
  void drawText();
  void drawEnemies();
  void drawEnemieBullets();

public:
  Gameplay(std::shared_ptr<Gamemanager>& gameMan);
  ~Gameplay();
  // Override functions
  void run() override;
  void poll() override;
  void update() override;
  void render() override;
};

#endif // !GAMEPLAY_H
