#include "compositeshape.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

CompositeShape::CompositeShape(const std::shared_ptr<Shape> &shape):
  array_(new  std::shared_ptr<Shape>[1]),
  size_(0)
{
  if (shape != nullptr)
  {
    array_[0] = shape;
    size_++;
  }
  else
  {
    throw std::invalid_argument("CompositeShape Constructor : trying to add nullptr in array");
  }
}

CompositeShape::CompositeShape(const CompositeShape &compositeShape):
  array_(new std::shared_ptr<Shape> [compositeShape.size_]),
  size_(compositeShape.size_)
{
  for (unsigned int i = 0; i < compositeShape.size_ ; i++)
  {
    array_[i] = compositeShape.array_[i];
  }
}

CompositeShape::CompositeShape(CompositeShape&& compositeShape) :
  array_(nullptr),
  size_(compositeShape.size_)

{
  compositeShape.size_ = 0;
  array_.swap(compositeShape.array_);
}

const std::shared_ptr<Shape> CompositeShape::operator [](unsigned int index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("CompositeShape operator [] : out of size range");
  }
  return array_[index];
}

CompositeShape &CompositeShape::operator=(const CompositeShape & compositeShape)
{
  if (&compositeShape != this)
  {
    CompositeShape tempCs(compositeShape);
    this->array_.swap(tempCs.array_);
    size_ = compositeShape.size_;
  }
  return *this;
}

CompositeShape &CompositeShape::operator=(CompositeShape&& compositeShape)
{
  array_.reset();
  size_ = compositeShape.size_;
  array_.swap(compositeShape.array_);
  compositeShape.size_= 0;
  return *this;
}

double CompositeShape::getArea() const noexcept
{
  double s = 0;
  for (unsigned int i = 0; i < size_ ; i++)
  {
    s += array_[i]->getArea();
  }
  return s;
}

rectangle_t CompositeShape::getFrameRect() const noexcept
{
  if (size_ > 0)
  {
    point_t center = {0,0};

    rectangle_t rect = array_[0]->getFrameRect();

    point_t left = {rect.pos.x - rect.width/2, rect.pos.y - rect.height/2};

    point_t right = {rect.pos.x + rect.width/2, rect.pos.y + rect.height/2};

    for (unsigned int i = 1; i < size_; i++)
    {
      rect = array_[i]->getFrameRect();

      if (rect.pos.x - rect.width/2 < left.x)
      {
        left.x = rect.pos.x - rect.width/2;
      }

      if (rect.pos.y - rect.height/2 < left.y)
      {
        left.y = rect.pos.y - rect.height/2;
      }

      if (rect.pos.x + rect.width/2 > right.x)
      {
        right.x = rect.pos.x + rect.width/2;
      }

      if (rect.pos.y + rect.height/2 > right.y)
      {
        right.y = rect.pos.y + rect.height/2;
      }
    }
    center.x = (left.x + right.x) / 2;
    center.y = (left.y + right.y) / 2;
    return {right.x - left.x, right.y - left.y, center};
  }
  else
  {
    return {0,0,{0,0}};
  }
}

unsigned int CompositeShape::getSize() const noexcept
{
  return size_;
}

MatrixShape CompositeShape::getSlayers() const
{
  MatrixShape tempMatr;
  for (unsigned int i = 0; i < size_ ; i++)
  {
    tempMatr.addToMatrix(array_[i]);
  }
  return tempMatr;
}

void CompositeShape::addToArray(const std::shared_ptr<Shape> &shape)
{
  if (shape == nullptr && shape.get() == this)
  {
    throw std::invalid_argument("CompositeShape addToArray : wrong parametr");
  }

  for (unsigned int i = 0; i < size_ ; i++)
  {
    if (array_[i] == shape)
    {
      throw std::invalid_argument("CompositeShape addToArray : shape already in array");
    }
  }

  array_type tempArray(new std::shared_ptr<Shape> [size_ + 1]);
  tempArray[size_] = shape;
  for (unsigned int i = 0; i < size_ ; i++)
  {
    tempArray[i] = array_[i];
  }
  array_.swap(tempArray);
  size_++;
}

void CompositeShape::removeFromArray(const unsigned int index)
{
  if (index < size_)
  {
    size_--;
    array_type tempArray(new std::shared_ptr<Shape>[size_]);
    for (unsigned int i = 0; i < index; i++)
    {
      tempArray[i] = array_[i];
    }
    for (unsigned int i = index; i < size_; i++)
    {
      tempArray[i] = array_[i+1];
    }
    array_.swap(tempArray);
  }
  else
  {
    throw std::out_of_range("CompositeShape removeFromArray : out of size range");
  }
}

void CompositeShape::move(const point_t &point) noexcept
{
  if (size_ > 0)
  {
    rectangle_t rect = getFrameRect();
    double dx = point.x - rect.pos.x;
    double dy = point.y - rect.pos.y;
    for (unsigned int i = 0; i < size_; i++)
    {
      array_[i]->move(dx, dy);
    }
  }
}

void CompositeShape::move(const double dx, const double dy) noexcept
{
  if (size_ > 0)
  {
    for (unsigned int i = 0; i < size_; i++)
    {
      array_[i]->move(dx, dy);
    }
  }
}

void CompositeShape::scale(const double coefficient)
{
  if (coefficient > 0 && size_ > 0)
  {
    point_t center = getFrameRect().pos;
    for (unsigned int i = 0; i < size_; i++)
    {
      rectangle_t rect = array_[i]->getFrameRect();

      array_[i]->move((coefficient - 1)*(rect.pos.x-center.x),
                      (coefficient - 1)*(rect.pos.y-center.y));

      array_[i]->scale(coefficient);
    }
  }
  else
  {
    throw std::invalid_argument("Composite shape scale : wrong parametr");
  }
}

void CompositeShape::turn(const double degrees) noexcept
{
  if (fmod(degrees, 360) != 0 && size_ > 0)
  {
    double tempCos = cos(degrees * M_PI / 180);
    double tempSin = sin(degrees * M_PI / 180);
    turn(tempCos, tempSin, getFrameRect().pos, degrees);
  }
}

void CompositeShape::turn(const double tempCos, const double tempSin, const point_t &rotateCenter, const double &degrees) noexcept
{
  for (unsigned int i = 0; i < size_; i++)
  {
    (*array_[i]).turn(tempCos,tempSin, rotateCenter, degrees);
  }
}


void CompositeShape::printInfo() const noexcept
{
  rectangle_t rect = getFrameRect();

  std::cout <<"Composite Shape :\n----------------------\nsize = "<<size_<< "\nArea = "
            << getArea() <<"\nFrameRect : \nWidth = "<<rect.width <<"\nHeight = "
            <<rect.height <<"\nCenter = (" <<rect.pos.x <<";"
            << rect.pos.y << ")" <<"\n=========\n" << "ARRAY INFO:\n";

  if (size_ == 0)
  {
    std::cout <<"Empty\n";
  }
  for (unsigned int i = 0; i <size_ ; i++)
  {
    std::cout << "Shape number " << i << ", ";
    array_[i]->printInfo();
    std::cout<<"\n";
  }
  std::cout << "\n";
}
