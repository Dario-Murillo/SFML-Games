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
  this->screen_map[id] = std::move(this->new_screen);
  this->currentScreen = id;
}

std::unique_ptr<Screen>& Screenmanager::getScreen(int id) {
  return this->screen_map[id];
}

std::unique_ptr<Screen>& Screenmanager::getCurrentScreen() {
  return this->screen_map[this->currentScreen];
}

void Screenmanager::setcurrentScreen(int new_screen) {
  this->currentScreen = new_screen;
}
