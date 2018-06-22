#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t &p, const double &w, const double &h);
  double getArea() const;
  rectangle_t getFrameRect() const;
  void setWidth(const double &w);
  void setHeight(const double &h);
  void move(const point_t &p);
  void move(const double &x, const double &y);	
  void printInfo() const;
private:
  double width_;
  double height_;
};
#endif
