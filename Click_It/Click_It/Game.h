#ifndef GAME_H
#define GAME_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>


#include "AssetManager.h"
#include "StateManager.h"

enum AssetID {
  MAIN_FONT = 0
};


/*
  Struct that manages the game assets, state and the main window
  by creating unique instances of each class
*/
struct GameManager {
  std::unique_ptr<Engine::AssetManager> assets;
  std::unique_ptr<Engine::StateManager> state;
  std::unique_ptr<sf::RenderWindow> window;

  GameManager() {
    this->assets = std::make_unique<Engine::AssetManager>();
    this->state = std::make_unique<Engine::StateManager>();
    this->window = std::make_unique<sf::RenderWindow>();
  }
};

/*
  The main game class that will
*/
class Game {
private:
  // Pointer to the game manager
  std::shared_ptr<GameManager> gameManager;
  // Video mode of the window
  sf::VideoMode videoMode;
  // Initializes window, it's called by the public constructor
  void initWindow();
public:
  Game();
  ~Game();
  void Start();
};

#endif // !GAME_H
