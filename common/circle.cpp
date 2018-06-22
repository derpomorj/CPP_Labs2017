#include "circle.hpp"
#include <iostream>
#include <cmath>

Circle::Circle(const point_t &point, const double radius) noexcept :
  radius_(radius),
  center_(point)
{
  if (radius_ < 0)
  {
    radius_ = -radius_;
  }
  else if (radius_ == 0)
  {
    radius_ = 1;
  }
}

double Circle::getArea() const noexcept
{
  return M_PI*radius_*radius_;
}

double Circle::getRadius() const noexcept
{
  return radius_;
}

point_t Circle::getCenter() const noexcept
{
  return center_;
}

rectangle_t Circle::getFrameRect() const noexcept
{
  return {2*radius_,2*radius_,center_};
}

void Circle::setRadius(const double radius) noexcept
{
  if (radius > 0)
  {
    radius_ = radius;
  }
  else if (radius < 0)
  {
    radius_ =-radius;
  }
  else if (radius == 0)
  {
    radius_ = 1;
  }
}

void Circle::move(const point_t &point) noexcept
{
  center_.x = point.x;
  center_.y = point.y;
}

void Circle::move(const double dx, const double dy) noexcept
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::scale(const double coefficient) noexcept
{
  if (coefficient < 0)
  {
    radius_ *= -coefficient;
  }
  else if (coefficient > 0)
  {
    radius_ *= coefficient;
  }
}

void Circle::printInfo() const noexcept
{
  rectangle_t rect = getFrameRect();
  std::cout << "circle:\ncenter=(" << center_.x << ";" << center_.y << ") \nradius=" << radius_ <<"\n"
            << "CIRCLE S=" << getArea() <<"\n" << "FrameRect: width="<<rect.width
            <<",heigth=" <<rect.height<<",pos=("<< rect.pos.x<< ";"
            <<rect.pos.y << ")\n";
}

void Circle::turn(const double) noexcept
{

}

void Circle::turn(const double tempCos, const double tempSin, const point_t &rotateCenter, const double &degrees) noexcept
{
  if (rotateCenter.x != center_.x || rotateCenter.y != center_.y || degrees != 0)
  {
    double x = center_.x;
    double y = center_.y;

    center_.x = rotateCenter.x + (x - rotateCenter.x)*tempCos  - (y - rotateCenter.y)*tempSin + 1 - 1;

    center_.y = rotateCenter.y + (x - rotateCenter.x)*tempSin + (y - rotateCenter.y)*tempCos + 1 - 1;
  }

}
