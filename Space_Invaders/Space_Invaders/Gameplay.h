#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Game.h"
#include "Spaceship.h"

class Gameplay : public Screen {

private:
  std::shared_ptr<Gamemanager>& gameManager;
  std::unique_ptr<Spaceship> heroe;

  // Boolean movement function
  bool moveLeft;
  bool moveRight;

  // Init functions
  void initVars();

  // Update functions
  void updateHeroe();


public:
  Gameplay(std::shared_ptr<Gamemanager>& gameMan);
  ~Gameplay();
  // Override functions
  void run() override;
  void poll() override;
  void update() override;
  void render() override;
};



#endif // !GAMEPLAY_H


