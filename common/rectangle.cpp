#include "rectangle.hpp"
#include <iostream>
#include <cmath>

Rectangle::Rectangle(const point_t &point, const double width, const double height) noexcept :
  center_(point),
  width_(width),
  height_(height),
  rotationAngle_(0)
{
  if (width_ < 0)
  {
    width_ = -width_;
  }
  else if (width_ == 0)
  {
    width_ = 1;
  }
  
  if (height_ < 0)
  {
    height_ = -height_;
  }
  else if (height_ == 0)
  {
    height_ = 1;
  }

  resetVertexes();
}

double Rectangle::getArea() const noexcept
{
  return width_*height_;
}

rectangle_t Rectangle::getFrameRect() const noexcept
{
  double width = std::max(vertex[2].x - vertex[0].x, vertex[3].x - vertex[1].x);
  double height = std::max(vertex[2].y - vertex[0].y, vertex[1].y - vertex[3].y);
  return {width, height, center_};
}

void Rectangle::setWidth(const double width) noexcept
{
  if (width > 0)
  {
    width_ = width;
  }
  else if (width < 0)
  {
    width_ = -width;
  }
  else if (width == 0)
  {
    width_= 1;
  }
  resetVertexes();
}

void Rectangle::setHeight(const double height) noexcept
{
  if (height > 0)
  {
    height_ = height;
  }
  else if (height < 0)
  {
    height_ = -height;
  } 
  else if (height == 0)
  {
    height_ =1;
  }
  resetVertexes();
}

void Rectangle::move(const point_t &point) noexcept
{
  double  dx = point.x -center_.x;
  double  dy = point.y -center_.y;
  center_.x = point.x;
  center_.y = point.y;
  for (int i = 0; i < 4 ; i++)
  {
    vertex[i].x += dx;
    vertex[i].y += dy;
  }
}


void Rectangle::move(const double dx, const double dy) noexcept
{
  center_.x += dx;
  center_.y += dy;
  for (int i = 0; i < 4 ; i++)
  {
    vertex[i].x += dx;
    vertex[i].y += dy;
  }
}

void Rectangle::scale(const double coefficient) noexcept
{
  if (coefficient < 0)
  {
	  height_ *= -coefficient;
	  width_ *= -coefficient;
  }
  else if (coefficient > 0)
  {
    height_ *= coefficient;
    width_ *= coefficient;
  }

  resetVertexes();
}

void Rectangle::turn(const double degrees)noexcept
{
  if (fmod(degrees, 180) != 0)
  {
    double tempCos = cos(degrees * M_PI / 180);
    double tempSin = sin(degrees * M_PI / 180);
    turn(tempCos, tempSin, center_, degrees);
  }
}

void Rectangle::turn(const double tempCos, const double tempSin , const point_t &rotateCenter, const double &degrees) noexcept
{
  double x = 0;
  double y = 0;
  rotationAngle_ = fmod(rotationAngle_ + degrees, 180);

  for (int i = 0; i < 4; i++)
  {
    x = vertex[i].x;
    y = vertex[i].y;
    vertex[i].x = rotateCenter.x + (x - rotateCenter.x) * tempCos - (y - rotateCenter.y) * tempSin + 10 - 10;
    vertex[i].y = rotateCenter.y + (x - rotateCenter.x) * tempSin + (y - rotateCenter.y) * tempCos + 10 - 10;
  }

  for (int i = 0; i < 3; i++)
  {
    for (int j = i + 1; j < 4; j++)
    {
      if (vertex[i].x > vertex[j].x)
      {
        std::swap(vertex[i], vertex[j]);
      }
    }
  }

  if (vertex[0].y > vertex[1].y)
  {
    std::swap(vertex[0], vertex[1]);
  }

  if (vertex[0].x > vertex[3].x)
  {
    std::swap(vertex[0], vertex[3]);
  }

  if (vertex[2].y < vertex[3].y)
  {
    std::swap(vertex[2], vertex[3]);
  }

  if (vertex[1].x > vertex[2].x)
  {
    std::swap(vertex[1], vertex[2]);
  }

  if (rotateCenter.x != center_.x || rotateCenter.y != center_.y)
  {
    center_.x = (vertex[0].x + vertex[2].x) / 2;
    center_.y = (vertex[0].y + vertex[2].y) / 2;
  }
}

point_t Rectangle::getVertex(unsigned int index) const
{
  if (index > 4)
  {
    return vertex[0];
  }
  return vertex[index];
}

void Rectangle::resetVertexes() noexcept
{
  vertex[0].x = center_.x - width_/2;
  vertex[0].y = center_.y - height_/2;

  vertex[1].x = vertex[0].x;
  vertex[1].y = center_.y + height_/2;

  vertex[2].x = center_.x + width_/2;
  vertex[2].y = vertex[1].y;

  vertex[3].x = vertex[2].x;
  vertex[3].y = vertex[0].y;

  if (rotationAngle_ != 0)
  {
    double tempAngle = rotationAngle_;
    rotationAngle_ = 0;
    turn(tempAngle);
  }
}

void Rectangle::printInfo() const noexcept
{
  rectangle_t rect = getFrameRect();
  std::cout << "rectangle:\ncenter=(" <<center_.x<<";"<<center_.y<<")\nwidth="<<width_
            << "\nrotation angle=" << rotationAngle_ <<"\nheight="<<height_<<"\nArea="
            <<getArea()<<"\nvertexes : (" << vertex[0].x <<";"<<vertex[0].y<< ") ("
            << vertex[1].x <<";"<<vertex[1].y << ") (" << vertex[2].x <<";"<<vertex[2].y
            << ") (" << vertex[3].x <<";"<<vertex[3].y << ")\nFrameRect: width="<<rect.width
            <<",heigth=" <<rect.height<<",pos=(" << rect.pos.x<< ";" <<rect.pos.y << ")\n";
}
