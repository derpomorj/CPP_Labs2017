#include "rectangle.hpp"
#include "circle.hpp"
#include "compositeshape.hpp"

int main()
{
  std::shared_ptr<Shape> rect( new Rectangle({0,0},1,1) );
  std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 2));
  std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({2, 2}, 3, 3));
  std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({0, 0},7));

  CompositeShape cs(rect);
  CompositeShape cs2(rect2);
  CompositeShape cs3(cs);

  cs.printInfo();
  cs2.printInfo();
  cs3.printInfo();
  cs2.move({1,2});
  cs3.addToArray(cir);
  cs3.move(12,12);
  cs3.removeFromArray(cs3.getSize() - 1);
  cs.printInfo();
  cs2.printInfo();
  cs3.printInfo();

  return 0;
}
