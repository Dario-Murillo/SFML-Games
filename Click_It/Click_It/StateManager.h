#ifndef STATE_MANGER_H
#define STATE_MANGER_H

#include <stack>
#include <memory>
#include "State.h"

/*
  Class that manages the state of the game by using a state stack
*/
namespace Engine {
  class StateManager {
  private:
    // Stack that contains current state of the game
    std::stack<std::unique_ptr<State>> state_stack;
    // New state to be execute and added to the stack
    // The stack should only be modified at the start of the update cycle
    std::unique_ptr<State> new_state;
    bool add;
    bool replace;
    bool remove;
  public:
    StateManager();
    ~StateManager();
    /*
      Pushes a new state into the stack
      @param new_state: new state to be added
      @param replace: boolean that indicates if the new state to be added will replace the current one
    */
    void push(std::unique_ptr<State> new_state, bool replace = false);
    // Deletes at the top of the stack
    void pop();
    // Function where the state stack will be modified
    void process();
    // Function that returns a unique pointer to the current state object by reference
    std::unique_ptr<State>& getCurrent();

  };
}


#endif // !STATE_MANGER_H