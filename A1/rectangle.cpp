#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const point_t &p, const double &w, const double &h):
  Shape(p),
  width_(w),
  height_(h)
{
  if (width_<0)
  {
    std::cerr<<"invalid width, replaced by absolute value \n";
    width_=-width_;
  }
  else if (width_==0)
  {
    std::cerr<<"invalid width, replaced by 1 \n";
    width_=1;
  }
  
  if (height_<0)
  {
    std::cerr<<"invalid height, replaced by absolute value \n";
    height_=-height_;
  }
  else if (width_==0)
  {
    std::cerr<<"invalid height, replaced by 1 \n";
    height_=1;
  }
}

double Rectangle::getArea() const
{
  return width_*height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_, height_, center_};
}

void Rectangle::setWidth(const double &w)
{
  if (w>0)
  {
    width_=w;
  }
  else if (width_<0)
  {
    std::cerr<<"invalid width, it will be replaced by absolute value \n";
    width_=-w;
  }
  else if (w==0)
  {
    std::cerr<<"invalid width, it will be replaced by 1 \n";
    width_=1;
  }
}

void Rectangle::setHeight(const double &h)
{
  if (h>0)
  {
    height_=h;
  }
  else if (h<0)
  {
    std::cerr<<"invalid height, it will be replaced by absolute value \n";
    height_=-h;
  } 
  else if (h==0)
  {
    std::cerr<<"invalid height,it will be replaced by 1 \n";
    height_=1;
  }
}

void Rectangle::move(const point_t &p)
{
  center_.x=p.x;
  center_.y=p.y;
}


void Rectangle::move(const double &x, const double &y)
{
  center_.x+=x;
  center_.y+=y;
}

void Rectangle::printInfo() const
{
  std::cout <<"\n**********************\n";
  std::cout << "rectangle info:\ncenter=(" <<center_.x<<";"<<center_.y<<")\nwidth="<<width_
              <<"\nheight="<<height_<<"\nArea="<<getArea();
  std::cout <<"\n**********************";
}
