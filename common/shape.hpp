#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const noexcept = 0;
  virtual rectangle_t getFrameRect() const noexcept = 0;
  virtual void move(const point_t &point) noexcept = 0;
  virtual void move(const double dx, const double dy) noexcept = 0;
  virtual void turn(const double degrees) noexcept = 0;
  virtual void turn(const double tempCos, const double tempSin, const point_t &rotateCenter, const double&) noexcept = 0;
  virtual void scale(const double coefficient) = 0;
  virtual void printInfo() const noexcept = 0;
};
#endif
