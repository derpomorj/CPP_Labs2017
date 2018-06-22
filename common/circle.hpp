#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t &point, const double radius) noexcept;

  double getArea() const noexcept;
  double getRadius() const noexcept;
  point_t getCenter() const noexcept;
  rectangle_t getFrameRect() const noexcept ;

  void setRadius(const double radius) noexcept;

  void move(const point_t &point) noexcept ;
  void move(const double dx, const double dy) noexcept ;

  void turn(const double) noexcept ;
  void scale(const double coefficient) noexcept;

  void printInfo() const noexcept ;
private:
  double radius_;
  point_t center_;

  void turn(const double, const double, const point_t &rotateCenter, const double &degrees) noexcept;
};
#endif
