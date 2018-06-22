#include "circle.hpp"
#include <iostream>
#include <cmath>

Circle::Circle(const double &x, const double &y, const double &R):
  Shape({x,y}),
  r_(R)
{
  if (r_<0)
  {
    std::cerr << "invalid radius, replaced by absolute value \n";
    r_=-r_;
  }
  else if (r_==0)
  {
    std::cerr << "invalid radius, replaced by 1 \n";
    r_=1;
  }
}

double Circle::getArea() const
{
  return M_PI*r_*r_;
}

double Circle::getRadius() const
{
  return r_;
}

point_t Circle::getCenter() const
{
  return center_;
}

rectangle_t Circle::getFrameRect() const
{
  return {2*r_,2*r_,center_};
}

void Circle::setRadius(const double &R) 
{
  if (r_>0)
  {
    r_=R;
  }
  else if (r_<0)
  {
    std::cerr << "invalid radius, replaced by absolute value \n";
    r_=-r_;
  }
  else if (r_==0)
  {
    std::cerr << "invalid radius, replaced by 1 \n";
    r_=1;
  }
}

void Circle::move(const point_t &p)
{
  center_.x=p.x;
  center_.y=p.y;
}

void Circle::move(const double &x, const double &y)
{
  center_.x+=x;
  center_.y+=y;
}

void Circle::printInfo() const
{
  std::cout <<"\n**********************\n";
  std::cout << "circle info:\ncenter=(" <<center_.x << ";" << center_.y << ") \nradius="<<r_<<"\n"
              << "CIRCLE S=" << getArea() <<"\n" << "FrameRect: width="<<getFrameRect().width
                <<",heigth=" <<getFrameRect().height<<",pos=("<< getFrameRect().pos.x<< ";" 
                  <<getFrameRect().pos.y << ")\n";
  std::cout <<"**********************\n";
}

