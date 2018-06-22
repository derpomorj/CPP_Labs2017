#include "Triangle.h"

Triangle::Triangle(int x, int y) :
  Shape(x, y)
{
}

void Triangle::draw(std::ostream &ostream) const
{
  ostream << "TRIANGLE " << '(' << x_ << "; " << y_ << ")\n";
}

