#ifndef MENU_H
#define MENU_H

#include "Game.h"
#include <SFML/Graphics.hpp>

class Menu : public Screen {
private:
  // Shared pointer
  std::shared_ptr<Gamemanager> gameManager;
public:
  Menu(std::shared_ptr<Gamemanager> gameMan);
  ~Menu();
  // Override functions
  void run() override;
  void poll() override;
  void update() override;
  void render() override;
};


#endif // !MENU_H

