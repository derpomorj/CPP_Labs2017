#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Shape.h"
#include <ostream>

class Circle : public Shape {
public:
  Circle(int, int);
  void draw(std::ostream&) const override;
};

#endif
