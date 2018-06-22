#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP

#include <memory>
#include "shape.hpp"
#include "matrixshape.hpp"

class CompositeShape : public Shape
{
  public:
  CompositeShape(const CompositeShape& compositeShape);
  CompositeShape(CompositeShape&& compositeShape);
  CompositeShape(const std::shared_ptr<Shape> &shape);

  const std::shared_ptr<Shape> operator [](unsigned int index) const;
  CompositeShape& operator=(const CompositeShape & compositeShape);
  CompositeShape& operator=(CompositeShape&& compositeShape);

  double getArea() const noexcept;
  rectangle_t getFrameRect() const noexcept;
  unsigned int getSize() const noexcept;
  MatrixShape getSlayers() const;

  void addToArray(const std::shared_ptr<Shape> &shape);
  void removeFromArray(const unsigned int index);

  void move(const point_t &point) noexcept ;
  void move(const double dx, const double dy) noexcept ;
  void turn(const double degrees) noexcept;
  void scale(const double coefficient);

  void printInfo() const noexcept;

  private:
  using array_type = std::unique_ptr<std::shared_ptr<Shape>[]>;
  array_type array_;

  unsigned int size_;

  void turn(const double tempCos, const double tempSin, const point_t &rotateCenter, const double &degrees) noexcept;
};

#endif
