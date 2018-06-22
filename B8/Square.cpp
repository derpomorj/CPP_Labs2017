#include "Square.h"

Square::Square(const int x, const int y) :
  Shape(x, y)
{
}

void Square::draw(std::ostream &ostream) const
{
  ostream << "SQUARE " << '(' << x_ << "; " << y_ << ")\n";
}

