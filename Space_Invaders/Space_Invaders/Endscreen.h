#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include "Game.h"

// Screen that manages the display and input after the game is over
class Endscreen : public Screen {
private:
  // Pointer to the main controller object of the game
  std::shared_ptr<Gamemanager> gameManager;
  // String to be displayed in the main title, is recived trought the constructor
  std::string mainText;
  // Font to display the texts
  sf::Font font;
  // Current position of the mouse
  sf::Vector2i mousePosition;
  sf::Vector2f mousePositionView;
  // Displays the contents of the string "mainText"
  sf::Text mainTitle;
  // Play title, when clicked it will go to the menu
  sf::Text menuTitle;
  // Exit title, when clicked it will close the game
  sf::Text exitTitle;
  // Init functions
  void initFonts();
  void initText();
  // Updates mouse position in the screen
  void updateMousePositions();
  // Updates text
  void updateText();
  // Draws the text
  // 
  void drawText(sf::RenderTarget &target);
public:
  /* Constructor
    @param gameMan, Pointer to the main controller object of the game
    @param mainText, The string that will be displayed in the main title
    it will consist of either "You Win" or "You Lose"
  */
  Endscreen(std::shared_ptr<Gamemanager> gameMan, std::string mainText);
  // Default destructor
  ~Endscreen();
  // Override functions
  void run() override;
  void poll() override;
  void update() override;
  void render() override;
};

#endif // !ENDSCREEN_H
