#ifndef MATRIXSHAPE_HPP
#define MATRIXSHAPE_HPP

#include <memory>
#include "shape.hpp"

class MatrixShape
{
  public:
  MatrixShape();
  MatrixShape(const MatrixShape& matrixShape);
  MatrixShape(MatrixShape&& matrixShape);
  MatrixShape(const std::shared_ptr<Shape> &shape);

  const std::shared_ptr<Shape> operator ()(unsigned int index, unsigned int index2) const;
  MatrixShape & operator=(const MatrixShape& matrixShape);
  MatrixShape & operator=(MatrixShape&& matrixShape);

  void addToMatrix(const std::shared_ptr<Shape> &shape);
  bool checkIntersection(const std::shared_ptr<Shape> &shape1, const std::shared_ptr<Shape> &shape2);

  unsigned int getNumberOfColumns();
  unsigned int getNumberOfRows();

  void printInfo() noexcept;

  private:
  using array_type = std::unique_ptr<std::shared_ptr<Shape>[]>;
  array_type matrix_;

  unsigned int numberOfColumns_;
  unsigned int numberOfRows_;
};

#endif
