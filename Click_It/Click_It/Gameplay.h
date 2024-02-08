#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <iostream>
#include <memory>
#include <ctime>
#include <sstream>
#include "Endscreen.h"
#include "Enemie.h"
#include "Game.h"
#include "State.h"

class Gameplay : public Engine::State {
private:
  std::shared_ptr<GameManager> gameManager;
  sf::Vector2i mousePosition;
  sf::Vector2f mousePositionView;
  void initEnemies();
  void initFonts();
  void initText();
  // Game Logic
  bool endGame;
  unsigned int points;
  float enemySpawnTimer;
  float enemySpawnTimerMax;
  int maxEnemies;
  bool mouseHeld;
  int health;

  // Resources
  sf::Font font;

  // Text
  sf::Text uiText;

  // Game objects
  std::vector<Enemie> enemies;
  Enemie enemie;
  // Functions
  void spawnEnemy();
  void updateMousePositions();
  void updateText();
  void updateEnemies();
  void renderEnemies(sf::RenderTarget& target);
  void renderText(sf::RenderTarget& target) const;
  void initVar();
public:
  Gameplay(std::shared_ptr<GameManager> gameMan);
  ~Gameplay();
  void init() override;
  void input() override;
  void update(sf::Time DeltaTime) override;
  void render() override;
  void Pause() override;
  void Start() override;
};

#endif // !GAMEPLAY_H


