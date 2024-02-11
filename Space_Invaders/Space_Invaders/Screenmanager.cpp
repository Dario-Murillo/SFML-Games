#include "Screenmanager.h"

Screenmanager::Screenmanager() {
  // First screen is gonna be the menu of the game
  this->currentScreen = MENU;
}

Screenmanager::~Screenmanager() {
  this->screen_map.clear();
}

void Screenmanager::addScreen(int id, std::unique_ptr<Screen> new_screen) {
  this->new_screen = std::move(new_screen);
  if (this->screen_map[id] != nullptr) {
    this->screen_map[id].reset();
    this->screen_map[id] = std::move(this->new_screen);
  }
  else {
    // We are inserting the state for the firstime
    this->screen_map[id] = std::move(this->new_screen);
  }
  this->currentScreen = id;
}

std::unique_ptr<Screen>& Screenmanager::getScreen(int id) {
  return this->screen_map[id];
}

std::unique_ptr<Screen>& Screenmanager::getCurrentScreen() {
  return this->screen_map[this->currentScreen];
}


