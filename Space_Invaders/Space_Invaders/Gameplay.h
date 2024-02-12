#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Game.h"
#include "Spaceship.h"

class Gameplay : public Screen {

private:
  std::shared_ptr<Gamemanager>& gameManager;
  // Heroe and bullets
  std::unique_ptr<Spaceship> heroe;
  std::vector<sf::RectangleShape> bullets;
  sf::RectangleShape bullet;

  // Boolean movement function
  bool moveLeft;
  bool moveRight;
  bool shoot;

  // Init functions
  void initVars();
  void initBullet();
  // Update functions
  void updateHeroe();
  void spawnBullet();
  void updateBullets();

  // Draw functions
  void drawBullets();


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


