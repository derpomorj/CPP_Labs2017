#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>

class Shape {
public:
  Shape(int, int);

  virtual ~Shape() = default;

  //bool isMoreLeft(const Shape*) const;
  bool isMoreLeft(const Shape&) const;

  //bool isUpper(const Shape*) const;
  bool isUpper(const Shape&) const;

  virtual void draw(std::ostream&) const = 0;

protected:
  int x_, y_;
};

#endif

