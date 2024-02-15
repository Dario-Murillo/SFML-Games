#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <sstream>
#include "Endscreen.h"
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

  // Enemie bullets and timer to shoot;
  std::vector<sf::RectangleShape> enemie_bullets;
  sf::RectangleShape enemie_bullet;
  sf::Clock enemie_bullet_clock;
  sf::Time time_since_last_bullet;
  sf::Time delta_time;
  bool spawn_enemie_bullet;
  float enemie_y_speed;
  float enemie_x_speed;

  // Text and Font
  sf::Font font;
  sf::Text points;
  sf::Text lives;

  // Game Points
  int point_count;

  // Enemies
  std::vector<std::unique_ptr<Enemie>> enemies;

  // Held
  bool shootHeld;

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
  void drawBullets(sf::RenderTarget& target);
  void drawText(sf::RenderTarget& target) const;
  void drawEnemies(sf::RenderTarget& target);
  void drawEnemieBullets(sf::RenderTarget& target);

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
