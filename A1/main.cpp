#include "rectangle.hpp"
#include "circle.hpp"

int main() 
{
  Circle circle(1,1,9);
  circle.printInfo();
	
  circle.setRadius(7);
  point_t p={-10,2};
  circle.move(p);
  circle.move(12,-10);
  circle.printInfo();

  Rectangle rect(p,2,9);
  rect.printInfo();
	
  rect.setWidth(12);
  rect.setHeight(0.5);
  rect.move({-9,7});
  rect.move(3,-4);
  rect.printInfo();
  return 0;
}
