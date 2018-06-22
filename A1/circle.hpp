#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const double &x, const double &y, const double &R);
  double getArea() const;
  double getRadius() const;
  point_t getCenter() const;
  rectangle_t getFrameRect() const;
  void setRadius(const double &R);
  void move(const point_t &p);
  void move(const double &x, const double &y);
  void printInfo() const;
private:
  double r_;
};
#endif
