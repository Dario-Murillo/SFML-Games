#ifndef PAUSE_H
#define PAUSE_H

#include "Game.h"
#include "Gameplay.h"
#include <SFML/Graphics.hpp>

// Screen that manages the game when the gameplay is paused
class Pause : public Screen {
private:
  // Pointer to the main controller object of the game
  std::shared_ptr<Gamemanager> gameManager;
  // Font to display the texts
  sf::Font font;
  // Mouse Positons
  sf::Vector2i mousePosition;
  sf::Vector2f mousePositionView;
  // Menu title, when clicked it will go to the menu and restart the game
  sf::Text menuTitle;
  // Continue title, when clicked it will resume the game
  sf::Text continueTitle;
  // Exit title, when clicked it will close the game
  sf::Text exitTitle;
  // Init functions
  void initFonts();
  void initText();
  // Updates mouse position in the screen
  void updateMousePositions();
  // Updates text
  void updateText();
public:
  /* Constructor
    @param gameMan, Pointer to the main controller object of the game
    @param mainText, The string that will be displayed in the main title
    it will consist of either "You Win" or "You Lose"
  */
  Pause(std::shared_ptr<Gamemanager>& gameMan);
  // Default destuctor
  ~Pause();
  // Override functions
  void run() override;
  void poll() override;
  void update() override;
  void render() override;
};

#endif // !PAUSE_H
