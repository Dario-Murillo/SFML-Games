#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "State.h"
#include "Game.h"
#include "Gameplay.h"


class Endscreen : public Engine::State {
private:
  std::shared_ptr<GameManager> gameManager;
  sf::Text endTitle;
public:
  Endscreen(std::shared_ptr<GameManager> gameMan);
  ~Endscreen();
  void init() override;
  void input() override;
  void update(sf::Time DeltaTime) override;
  void render() override;
};

#endif // !ENDSCREEN_H


