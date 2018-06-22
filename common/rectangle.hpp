#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.hpp"

class Rectangle : public Shape
{
  public:
  Rectangle(const point_t &point, const double width, const double height) noexcept ;

  double getArea() const noexcept;
  rectangle_t getFrameRect() const noexcept;
  point_t getVertex(unsigned int index) const;

  void setWidth(const double width) noexcept ;
  void setHeight(const double height) noexcept ;

  void move(const point_t &point) noexcept;
  void move(const double dx, const double dy) noexcept;

  void turn(const double degrees) noexcept ;
  void scale(const double coefficient) noexcept;
  void resetVertexes() noexcept;

  void printInfo() const noexcept;

  private:
  point_t center_;
  double width_;
  double height_;
  double rotationAngle_;
  point_t vertex[4];

  void turn(const double tempCos, const double tempSin, const point_t &rotateCenter, const double &degrees) noexcept;
};

#endif
