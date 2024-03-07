#ifndef MENU_H
#define MENU_H

#include "Game.h"
#include "Gameplay.h"
#include <SFML/Graphics.hpp>

// Screen that manages the display and input before the gameplay
class Menu : public Screen {
private:
  // Texture/image of the background of the screen
  sf::Texture texture;
  // Background image of the menu
  sf::Sprite background;
  // Pointer to the main controller object of the game
  std::shared_ptr<Gamemanager> gameManager;
  // Font to display the text
  sf::Font font;
  // Mouse Positons on the screen
  sf::Vector2i mousePosition;
  sf::Vector2f mousePositionView;
  // Main title of the game will display "Space Invaders"
  sf::Text mainTitle;
  // Play title, when clicked it will start the game
  sf::Text playTitle;
  // Exit title, when clicked it will close the game
  sf::Text exitTitle;
  // Init functions
  void initFonts();
  void initText();
  void initSprite();
  // Updates mouse position in the screen
  void updateMousePositions();
  // Updates text
  void updateText();
  // Draws the text and background
  void drawText(sf::RenderTarget &target) const;
public:
  /*
    Constructor:
    @param gameMan, Pointer to the main controller object of the game
  */
  Menu(std::shared_ptr<Gamemanager>& gameMan);
  // Default destructor
  ~Menu();
  // Override functions
  void run() override;
  void poll() override;
  void update() override;
  void render() override;
};

#endif // !MENU_H
