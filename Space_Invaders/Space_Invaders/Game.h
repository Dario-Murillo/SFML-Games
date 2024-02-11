#ifndef GAME_H
#define GAME_H

#include "Screenmanager.h"

/* A struct that is gonna act as a manager of the game 
  @members:
  window: The render window of the game
  screen_manager: Unique instance of a screen manager object that will be the responsible of adding, removing and changing screens
*/
struct Gamemanager {
  std::unique_ptr<Screenmanager> screen_manager;
  std::unique_ptr<sf::RenderWindow> window;

  // Constructor that creates the instances of the unique pointes members
  Gamemanager() {
    this->window = std::make_unique<sf::RenderWindow>();
    this->screen_manager = std::make_unique<Screenmanager>();
  }
};

class Game {
private:
  /* Shared pointer to an instance of the Gamemanagers, that will be passed to every class that acts as a screen 
    this pointer is used to manipulate the instances inside it (the window and the screen manager).
  */ 
  std::shared_ptr<Gamemanager> gameManager;
  // Viewmode to be used in the main window
  sf::VideoMode viewmode;
  // Init functions
  void initWindow();
public:
  // Starts the game
  void start();
  // Constructor, calls the init funcionts and creates the shared pointer of gameManager
  Game();
  // Default destructor
  ~Game();
};


#endif // !GAME_H
