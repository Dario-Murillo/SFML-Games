#include <stdlib.h>
#include "Game.h"

int main() {
  std::srand(static_cast<unsigned>(time(NULL)));
  Game game;
  game.start();
  return EXIT_SUCCESS;
}
