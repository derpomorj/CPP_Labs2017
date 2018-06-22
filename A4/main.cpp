#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "compositeshape.hpp"
#include "matrixshape.hpp"

int main()
{
  try
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 4));
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3, 4}, 2, 1));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({8, 3}, 2, 2));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({4.5, 5.5}, 2, 2));
    std::shared_ptr<Shape> rect4 = std::make_shared<Rectangle>(Rectangle({5.1, 6.2}, 1.3, 1.3));
    std::shared_ptr<Shape> rect5 = std::make_shared<Rectangle>(Rectangle({4.5, 1.5}, 1, 1));
    std::shared_ptr<Shape> cir1 = std::make_shared<Circle>(Circle({4.5, 1.5}, 1));
    CompositeShape cs(rect);
    cs.addToArray(rect1);
    cs.addToArray(rect2);
    cs.addToArray(rect3);
    cs.addToArray(rect4);
    cs.addToArray(rect5);
    cs.addToArray(cir1);
    cs.printInfo();
    cs.turn(45);
    cs.printInfo();
    MatrixShape ms = cs.getSlayers();
    ms.printInfo();
  }
  catch (std::invalid_argument exception)
  {
    std::cout << exception.what();
  }
  catch (std::out_of_range exception)
  {
    std::cout << exception.what();
  }
  catch (...)
  {
    std::cout << "exception";
  }
  return 0;
}
