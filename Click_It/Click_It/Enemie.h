#ifndef ENEMIE_H
#define ENEMIE_H

#include <SFML/Graphics.hpp>

class Enemie {
private:
  int valuePoints;
public:
  // Figure must be public. Why? I don't know but otherwise it won't work
  sf::RectangleShape figure;
  int getValuePoints() const;
  Enemie();
  Enemie(int type);
  ~Enemie();
};

#endif // ENEMIE_H

