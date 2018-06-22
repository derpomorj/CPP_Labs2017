#include "rectangle.hpp"
#include "circle.hpp"

int main() 
{
  point_t p = {1,1};
  Circle circle(p,1);
  circle.printInfo();
	
  circle.setRadius(7);
  p={-10,2};
  circle.move(p);
  circle.scale(2);
  circle.move(12,-10);
  circle.printInfo();

  Rectangle rect(p,2,9);
  rect.printInfo();
	
  rect.setWidth(12);
  rect.setHeight(0.5);
  rect.move({-9,7});
  rect.move(3,-4);
  rect.scale(1.4);
  rect.printInfo();
  return 0;
}
