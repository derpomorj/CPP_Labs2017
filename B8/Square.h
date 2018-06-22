#ifndef SQUARE_H
#define SQUARE_H

#include "Shape.h"

class Square : public Shape {
public:
  Square(int x, int y);

  void draw(std::ostream&) const override;
};

#endif 

