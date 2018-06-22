#include "matrixshape.hpp"
#include <stdexcept>
#include <iostream>

MatrixShape::MatrixShape() :
  matrix_(new std::shared_ptr<Shape>[0]),
  numberOfColumns_(0),
  numberOfRows_(0)
{

}

MatrixShape::MatrixShape(const std::shared_ptr<Shape> &shape):
  matrix_(nullptr),
  numberOfColumns_(0),
  numberOfRows_(0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("can`t add nullptr in matrix shape");
  }
  matrix_.reset(new std::shared_ptr<Shape>[1]);
  matrix_[0] = shape;
  ++numberOfRows_;
  ++numberOfColumns_;
}

MatrixShape::MatrixShape(const MatrixShape &matrixShape):
  matrix_(new std::shared_ptr<Shape>[matrixShape.numberOfRows_ * matrixShape.numberOfColumns_]),
  numberOfColumns_(matrixShape.numberOfColumns_),
  numberOfRows_(matrixShape.numberOfRows_)
{
  for (unsigned int i = 0; i < numberOfColumns_ * numberOfRows_ ; i++)
  {
    matrix_[i] = matrixShape.matrix_[i];
  }
}

MatrixShape::MatrixShape(MatrixShape&& matrixShape):
  matrix_(nullptr),
  numberOfColumns_(matrixShape.numberOfColumns_),
  numberOfRows_(matrixShape.numberOfRows_)
{
  matrix_.swap(matrixShape.matrix_);
  matrixShape.numberOfRows_ = 0;
  matrixShape.numberOfColumns_ = 0;
}

const std::shared_ptr<Shape> MatrixShape::operator()(unsigned int row ,unsigned int collumn) const
{
  unsigned int index = row * numberOfColumns_ + collumn;
  if (index >= numberOfRows_*numberOfColumns_ || row >= numberOfRows_ || collumn >= numberOfColumns_)
  {
    throw std::out_of_range("MatrixShape operator () : out of size range");
  }
  return matrix_[index];
}

MatrixShape &MatrixShape::operator=(const MatrixShape& matrixShape)
{
  MatrixShape ms(matrixShape);
  this->matrix_.swap(ms.matrix_);
  this->numberOfRows_ = ms.numberOfRows_;
  this->numberOfColumns_ = ms.numberOfColumns_;
  return *this;
}

MatrixShape &MatrixShape::operator=(MatrixShape&& matrixShape)
{
  matrix_.reset();
  numberOfColumns_ = matrixShape.numberOfColumns_;
  numberOfRows_ = matrixShape.numberOfRows_;
  matrix_.swap(matrixShape.matrix_);
  matrixShape.numberOfRows_ = 0;
  matrixShape.numberOfColumns_ = 0;
  return *this;
}

void MatrixShape::addToMatrix(const std::shared_ptr<Shape> &shape)
{

  if (shape == nullptr)
  {
    throw std::invalid_argument("cant add nullptr in matrix");
  }
  if (numberOfRows_ == 0)
  {
    matrix_.reset(new std::shared_ptr<Shape>[1]);
    matrix_[0] = shape;
    numberOfRows_++;
    numberOfColumns_++;
    return;
  }
  for (unsigned int i=0; i < numberOfColumns_ * numberOfRows_; i++)
  {
    if (matrix_[i] == shape)
    {
      throw std::invalid_argument("Shape already in matrix");
    }
  }

  unsigned int layer = 1;

  for (unsigned int i = numberOfRows_ -1 ;; i--) //определение слоя, на который нужно поместить фигуру
  {
    for (unsigned int j = numberOfColumns_ -1 ;; j--)
    {
      if (matrix_[i * numberOfColumns_ + j] != nullptr)
      {
        if (checkIntersection(matrix_[i * numberOfColumns_ + j], shape))
        {
          layer = i + 2;
          goto stop;
        }
      }
      if (j == 0)
      {
        break;
      }
    }
    if (i == 0)
    {
      break;
    }
  }
  stop:

  if (layer > numberOfRows_)
  {
    array_type tempMatrix(new std::shared_ptr<Shape>[(numberOfRows_ + 1)*numberOfColumns_]);

    for (unsigned i=0; i < numberOfRows_ * numberOfColumns_; i++)
    {
      tempMatrix[i] = matrix_[i];
    }

    tempMatrix[ numberOfRows_ * numberOfColumns_] = shape;

    for (unsigned i = numberOfRows_ * numberOfColumns_ +1 ; i < (numberOfRows_ + 1) * numberOfColumns_; i++)
    {
      tempMatrix[i] = nullptr;
    }

    matrix_.swap(tempMatrix);

    numberOfRows_++;
    return;
  }
  else
  {
    for (unsigned int i = (layer-1)*numberOfRows_; i < (layer-1)*numberOfRows_ + numberOfColumns_; i++ )
    {
      if (matrix_[i] == nullptr)
      {
        matrix_[i] = shape;
        return;
      }
    }
    array_type tempMatrix(new std::shared_ptr<Shape>[numberOfRows_ * (numberOfColumns_ + 1)]);

    for (unsigned int i = 0; i < numberOfRows_; i++)
    {
      for (unsigned int j = 0; j < numberOfColumns_; j++)
      {
        tempMatrix[i * (numberOfColumns_+1) + j] = matrix_[i*numberOfColumns_ + j];
      }
    }

    for (unsigned int i = 0; i < numberOfRows_; i++)
    {
      tempMatrix[i * (numberOfColumns_ + 1) + numberOfColumns_] = nullptr;
    }

    tempMatrix[(layer -1)*(numberOfColumns_ + 1) + numberOfColumns_] = shape;

    matrix_.swap(tempMatrix);
    numberOfColumns_++;
    return;
  }
}

bool MatrixShape::checkIntersection(const std::shared_ptr<Shape> &shape1, const std::shared_ptr<Shape> &shape2)
{
  if (shape1 == nullptr || shape2 == nullptr)
  {
    throw std::invalid_argument("cant compare nulptr");
  }
  rectangle_t rect1 = shape1->getFrameRect();
  rectangle_t rect2 = shape2->getFrameRect();
  point_t TopShape1 = {rect1.pos.x - rect1.width / 2, rect1.pos.y + rect1.height / 2};
  point_t BotShape1 = {rect1.pos.x + rect1.width / 2, rect1.pos.y - rect1.height / 2};

  point_t TopShape2 = {rect2.pos.x - rect2.width / 2, rect2.pos.y + rect2.height / 2};
  point_t BotShape2 = {rect2.pos.x + rect2.width / 2, rect2.pos.y - rect2.height / 2};

  return !(TopShape1.y < BotShape2.y || BotShape1.y > TopShape2.y
           || BotShape1.x < TopShape2.x || TopShape1.x > BotShape2.x);
}

unsigned int MatrixShape::getNumberOfColumns()
{
  return numberOfColumns_;
}

unsigned int MatrixShape::getNumberOfRows()
{
  return numberOfRows_;
}

void MatrixShape::printInfo() noexcept
{
  std::cout << "\nmatrix shape info: \n"
            << "====================\n"
            << "number of Columns : " << numberOfColumns_
            << "\nnumber of rows : " << numberOfRows_ << "\n\n";

  for (unsigned int i = 0; i < numberOfRows_; i++)
  {
    std::cout << "layer number " << i+1 << ":\n\n";
    for (unsigned int j = 0; j < numberOfColumns_; j++)
    {
      if (matrix_[i * numberOfColumns_ + j] != nullptr)
      {
        matrix_[i * numberOfColumns_ + j]->printInfo();
        std::cout << "\n";
      }
    }

  }
}
