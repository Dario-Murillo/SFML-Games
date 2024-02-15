#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include "Game.h"

class Endscreen : public Screen {
private:
  std::shared_ptr<Gamemanager> gameManager;
  // String
  std::string mainText;

  // Font
  sf::Font font;

  // Mouse Positons
  sf::Vector2i mousePosition;
  sf::Vector2f mousePositionView;

  // Text to be displayed 
  sf::Text mainTitle;
  sf::Text menuTitle;
  sf::Text exitTitle;

  // Init functions
  void initFonts();
  void initText();


  // Updates mouse position in the screen
  void updateMousePositions();
  // Updates text
  void updateText();
public:
  Endscreen(std::shared_ptr<Gamemanager> gameMan, std::string mainText);
  ~Endscreen();
  // Override functions
  void run() override;
  void poll() override;
  void update() override;
  void render() override;
};

#endif // !ENDSCREEN_H
