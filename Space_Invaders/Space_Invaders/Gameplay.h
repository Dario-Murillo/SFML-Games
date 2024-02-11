#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Game.h"


class Gameplay : public Screen {

private:
  std::shared_ptr<Gamemanager>& gameManager;

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


