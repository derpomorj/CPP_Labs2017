#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Shape.h"

class Triangle : public Shape {
public:
  Triangle(int x, int y);

  void draw(std::ostream&) const override;
};

#endif
