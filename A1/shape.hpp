#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

class Shape
{
protected:
  point_t center_;
public:
  Shape(const point_t &p);
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t &p)=0;
  virtual void move(const double &x, const double &y)=0;
};
#endif
