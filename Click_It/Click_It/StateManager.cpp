#include "StateManager.h"

Engine::StateManager::StateManager() : add(false), replace(false), remove(false) {}

Engine::StateManager::~StateManager() {}

void Engine::StateManager::push(std::unique_ptr<State> new_state, bool replace) {
  this->add = true;
  this->new_state = std::move(new_state);
  this->replace = replace;
}

void Engine::StateManager::pop() {
  this->remove = true;
}

void Engine::StateManager::process() {
  if (this->remove && !this->state_stack.empty()) {
    this->state_stack.pop();
    if (!this->state_stack.empty()) {
      this->state_stack.top()->Start();
    }
    this->remove = false;
  }
  if (this->add) {
    if (this->replace && (!this->state_stack.empty())) {
      this->state_stack.pop();
      this->replace = false;
    }
    if (!this->state_stack.empty()) {
      this->state_stack.top()->Pause();
    }
    this->state_stack.push(std::move(this->new_state));
    this->state_stack.top()->init();
    this->state_stack.top()->Start();
    this->add = false;
  }
}

std::unique_ptr<Engine::State>& Engine::StateManager::getCurrent() {
  return this->state_stack.top();
  // TODO: Insertar una instrucción "return" aquí
}
