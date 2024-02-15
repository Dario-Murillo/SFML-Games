#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <map>
#include <memory>
#include <iostream>
#include "Screen.h"

/* Enumerates the state/screen of the game */
enum State {
  MENU = 0,
  GAMEPLAY = 1,
  ENDSCREEN = 2
};

/* Class that manages the screens of the game, is responsible of adding, deleting and changing the screens */
class Screenmanager {
private:
  /* Map that directs integers (from the enum) to unique pointers of instances of different screens */
  std::map<int, std::unique_ptr<Screen>> screen_map;
  /* Pivot that helps move and add instances of the new_screen. Necessary in order to move unique pointers */
  std::unique_ptr<Screen> new_screen;
  /* Integer that indicates the current state/screen that is being display */
  int currentScreen;
public:
  //void add_and_replce(int id, std::unique_ptr<Screen> new_screen);
  /*
    Adds new screens to the map and changes to it, in case there was a screen maped to a state
    the functions deletes the instance of the screen and replaces it with the new one.
    @param id: Indicates the id to be used to map the new screen
    @param new_screen: Unique pointer that contains the new screen to be added
  */
  void addScreen(int id, std::unique_ptr<Screen> new_screen);
  /*
    Returns the screen of the map indicated by the id param
    @param id: Indicates the id of the screen that should be returned
    @return null pointer in case the screen indicated by the id doesn't exist
            otherwise it returns the instance of the screen
  */
  std::unique_ptr<Screen>& getScreen(int id);
  /*
    @see getScreen, it does the same but instead of and id picked by the user, it returns
    the instance of the screen indicated my the member currentScreen
  */
  std::unique_ptr<Screen>& getCurrentScreen();
  // Default constructor
  Screenmanager();
  // Destructor, clears the map so the unique pointers on it are out of the scope and are cleared
  ~Screenmanager();


};

#endif // !SCREENMANAGER_H


