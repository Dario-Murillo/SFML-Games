#ifndef STATE_H
#define STATE_H

#include <SFML/System/Time.hpp>

/*
  Wrapper class to control the state of the game
*/
namespace Engine {
  class State {
  public:
    State() {};
    virtual ~State() {};
    virtual void init() = 0;
    // Input == Polling
    virtual void input() = 0;
    // window.setFrameRate(60), delta time manages the FPS
    virtual void update(sf::Time DeltaTime) = 0;
    virtual void render() = 0;

    // Blank implementation for now, user can decide wheter they want to implement it or not
    virtual void Pause() {};
    virtual void Start() {};
  };
}

#endif // STATE_H
