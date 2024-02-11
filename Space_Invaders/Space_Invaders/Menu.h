#ifndef MENU_H
#define MENU_H

#include "Game.h"
#include "Gameplay.h"
#include <SFML/Graphics.hpp>

class Menu : public Screen {
private:
  // Shared pointer
  std::shared_ptr<Gamemanager> gameManager;

  // Font
  sf::Font font;

  // Mouse Positons
  sf::Vector2i mousePosition;
  sf::Vector2f mousePositionView;

  // Text to be displayed 
  sf::Text mainTitle;
  sf::Text playTitle;
  sf::Text exitTitle;

  // Init functions
  void initFonts();
  void initText();


  // Updates mouse position in the screen
  void updateMousePositions();
  // Updates text
  void updateText();
public:
  Menu(std::shared_ptr<Gamemanager>& gameMan);
  ~Menu();
  // Override functions
  void run() override;
  void poll() override;
  void update() override;
  void render() override;
};


#endif // !MENU_H

