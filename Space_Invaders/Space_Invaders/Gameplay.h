#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <sstream>
#include "Endscreen.h"
#include "Enemie.h"
#include "Game.h"
#include "Pause.h"
#include "Spaceship.h"

// Screen that manages and displays the main game logic
class Gameplay : public Screen {
private:
  // Pointer to the main controller object of the game
  std::shared_ptr<Gamemanager>& gameManager;
  // Unique instance of the player
  std::unique_ptr<Spaceship> heroe;
  // Vector of rectangle shapes that simulate bullets
  std::vector<sf::RectangleShape> bullets;
  // Rectangle shape that constructs the bullets object that later will be emplaced in the bullets array
  sf::RectangleShape bullet;
  // Vector of rectangle shapes that simulate the enemies bullets
  std::vector<sf::RectangleShape> enemie_bullets;
  // Rectangle shape that constructs the enemie bullets object that later will be emplaced in the bullets array
  sf::RectangleShape enemie_bullet;
  // Integer that stores the original size (number) of enemies
  int originalSize;
  // Clock object to keep track of the time elapsed in the game
  sf::Clock enemie_bullet_clock;
  // Time object that indicates how much time has passed since the enemies shoot their bullets
  sf::Time time_since_last_bullet;
  // Boolean that indicates wether enemies can shoot or not
  bool spawn_enemie_bullet;
  // The speed of the enemies in the vertical axis
  float enemie_y_speed;
  // The speed of the enemies in the horizontal
  float enemie_x_speed;
  // Font that will be used to display the text in game
  sf::Font font;
  // Text that displays how many points the player currently has
  sf::Text points;
  // Text that displays how many lives the player currently has
  sf::Text lives;
  // Integer that COUNTS how many points the player has (this is displayed in the screen with @see points)
  int point_count;
  // A vector of unique pointers that will allocate the enemies of the game
  std::vector<std::unique_ptr<Enemie>> enemies;
  // Boolean function to prevent the player from holding the space bar and spamming bullets
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
  /*
    Constuctor:
    @param gameMan, Pointer to the main controller object of the game
  */
  Gameplay(std::shared_ptr<Gamemanager>& gameMan);
  // Default destructor
  ~Gameplay();
  // Override functions
  void run() override;
  void poll() override;
  void update() override;
  void render() override;
};

#endif // !GAMEPLAY_H
