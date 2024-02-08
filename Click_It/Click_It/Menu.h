#ifndef MENU_H
#define MENU_H

#include "State.h"
#include "Game.h"
#include "Gameplay.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu : public Engine::State {
private:
  std::shared_ptr<GameManager> gameManager;
  sf::Text gameTitle;
  sf::Vector2i mousePosition;
  sf::Vector2f mousePositionView;
  // Updates the current position of the mouse on the screen
  void updateMousePositions();
public:
  Menu(std::shared_ptr<GameManager>& gameMan);
  ~Menu();
  void init() override;
  void input() override;
  void update(sf::Time DeltaTime) override;
  void render() override;
};



#endif // !MENU_H
