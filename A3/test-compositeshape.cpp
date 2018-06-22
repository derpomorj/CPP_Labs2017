#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "compositeshape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

  BOOST_AUTO_TEST_CASE(CopyConstructorTest)
  {
    std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({0,0},1));
    CompositeShape cs(cir);
    CompositeShape cs1(cs);
    BOOST_CHECK(cs1[0] == cs[0]);
    BOOST_CHECK(cs1.getSize() == 1);
  }

  BOOST_AUTO_TEST_CASE(ConstructorTest)
  {
    std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({0,0},1));
    CompositeShape cs(cir);
    BOOST_CHECK(cs.getSize()==1);
    BOOST_CHECK(cs[0] == cir);
  }

  BOOST_AUTO_TEST_CASE(ConstructorWrongParameter1)
  {
    std::shared_ptr<Shape> cir = nullptr;
    BOOST_CHECK_THROW(CompositeShape cs(cir),std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(OverloadOperatorTest)
  {
    std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({1,1},1));
    CompositeShape cs(cir);
    BOOST_CHECK(cs[0] == cir);
  }

  BOOST_AUTO_TEST_CASE(OverloadOperatorWrongParametr1)
  {
    std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({0,0},1));
    CompositeShape cs(cir);
    BOOST_CHECK_THROW(cs[1013], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(GetSizeTest)
  {
    std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({0,0},1));
    CompositeShape cs(cir);
    BOOST_CHECK(cs.getSize()==1);
  }

  BOOST_AUTO_TEST_CASE(GetAreaTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1,1},9,1));
    std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({1,1},1));
    CompositeShape cs(cir);
    cs.addToArray(rect);
    BOOST_CHECK_CLOSE(cs.getArea(),9+M_PI,0.001);
  }

  BOOST_AUTO_TEST_CASE(GetAreaZeroSizeTest)
  {
    std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({0,0},1));
    CompositeShape cs(cir);
    cs.removeFromArray(0);
    BOOST_CHECK(cs.getArea() == 0);
  }

  BOOST_AUTO_TEST_CASE(GetFrameRectTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({0,0},9,4));
    std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({1,1},1));
    CompositeShape cs(cir);
    cs.addToArray(rect);
    rectangle_t FrameRect = cs.getFrameRect();
    BOOST_CHECK_CLOSE(FrameRect.pos.x,0,0.001);
    BOOST_CHECK_CLOSE(FrameRect.pos.y,0,0.001);
    BOOST_CHECK_CLOSE(FrameRect.width,9,0.001);
    BOOST_CHECK_CLOSE(FrameRect.height,4,0.001);
  }

  BOOST_AUTO_TEST_CASE(GetFrameRectTestZeroSize)
  {
    std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({1,1},1));
    CompositeShape cs(cir);
    cs.removeFromArray(0);
    rectangle_t FrameRect = cs.getFrameRect();
    BOOST_CHECK(FrameRect.pos.x == 0);
    BOOST_CHECK(FrameRect.pos.y==0);
    BOOST_CHECK(FrameRect.width == 0);
    BOOST_CHECK(FrameRect.height == 0);
  }


  BOOST_AUTO_TEST_CASE(AddToArrayCircle)
  {
    std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({1,1},1));
    std::shared_ptr<Shape> cir2 = std::make_shared<Circle>(Circle({1,1},1));
    CompositeShape cs(cir);
    cs.addToArray(cir2);
    BOOST_CHECK(cs[1] == cir2);
    BOOST_CHECK(cs.getSize()==2);
    BOOST_CHECK(cs[1]->getArea() == M_PI);
  }

  BOOST_AUTO_TEST_CASE(AddToArrayRectangleTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1,1},1,1));
    CompositeShape cs(rect);
    BOOST_CHECK(cs.getSize()==1);
    BOOST_CHECK(cs[0]->getArea()==1);
  }

  BOOST_AUTO_TEST_CASE(RemoveFromarrayTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1,1},1,1));
    CompositeShape cs(rect);
    cs.removeFromArray(0);
    BOOST_CHECK(cs.getSize() == 0);
  }

  BOOST_AUTO_TEST_CASE(RemoveFromarrayTest_NULL_array)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1,1},1,1));
    CompositeShape cs(rect);
    cs.removeFromArray(0);
    BOOST_CHECK_THROW(cs.removeFromArray(0), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(RemoveFromarrayTest_WrongParametr)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1,1},1,1));
    CompositeShape cs(rect);
    BOOST_CHECK_THROW(cs.removeFromArray(212), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointTest)
  {
    point_t p={10,10};
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({0,0},1,1));
    std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({0,0},1));
    CompositeShape cs(cir);
    cs.addToArray(rect);
    cs.move(p);
    rectangle_t rect0 = cs.getFrameRect();
    rectangle_t rect00 = cs.getFrameRect();
    BOOST_CHECK(rect0.pos.x == 10);
    BOOST_CHECK(rect00.pos.x == 10);
    BOOST_CHECK(rect0.pos.y == 10);
    BOOST_CHECK(rect00.pos.y == 10);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointAreaConst)
  {
    point_t p={10,10};
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({0,0},1,1));
    std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({0,0},1));
    CompositeShape cs(cir);
    cs.addToArray(rect);
    double S = cs.getArea();
    cs.move(p);
    double S1 = cs.getArea();
    BOOST_CHECK_CLOSE(S,S1,0.001);
  }

  BOOST_AUTO_TEST_CASE(MoveXY_Test)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({0,0},1,1));
    std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({0,0},1));
    CompositeShape cs(cir);
    cs.addToArray(rect);
    cs.move(10,10);
    rectangle_t rect0 = cs.getFrameRect();
    rectangle_t rect00 = cs.getFrameRect();
    BOOST_CHECK(rect0.pos.x == 10);
    BOOST_CHECK(rect00.pos.x == 10);
    BOOST_CHECK(rect0.pos.y == 10);
    BOOST_CHECK(rect00.pos.y == 10);
  }

  BOOST_AUTO_TEST_CASE(MoveXY_AreaConst)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({0,0},1,1));
    std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({0,0},1));
    CompositeShape cs(cir);
    cs.addToArray(rect);
    double S = cs.getArea();
    cs.move(21,44);
    double S1 = cs.getArea();
    BOOST_CHECK_CLOSE(S,S1,0.001);
  }

  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({0,0},1,1));
    std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({0,0},1));
    CompositeShape cs(rect);
    cs.addToArray(cir);
    cs.scale(2);
    BOOST_CHECK_CLOSE(cs.getArea(),4+4*M_PI,0.01);
  }

  BOOST_AUTO_TEST_CASE(ScaleWrongParametr)
  {
    std::shared_ptr<Shape> cir = std::make_shared<Circle>(Circle({0,0},1));
    CompositeShape cs(cir);
    BOOST_CHECK_THROW(cs.scale(-22),std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MoveConstructorTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 4));
    CompositeShape cs(rect);
    CompositeShape cs2(std::move(cs));
    BOOST_CHECK_THROW(cs[0], std::out_of_range);
    BOOST_CHECK(cs2[0] == rect);
    BOOST_CHECK(rect.use_count() == 2);
  }

  BOOST_AUTO_TEST_CASE(MoveOperatorTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 4));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({11, 1}, 2, 4));
    CompositeShape cs(rect);
    CompositeShape cs2(rect2);
    cs2 = std::move(cs);
    BOOST_CHECK_THROW(cs[0], std::out_of_range);
    BOOST_CHECK(cs2[0] == rect);
    BOOST_CHECK(rect2.use_count() == 1);
  }

  BOOST_AUTO_TEST_CASE(GetSlayersTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 4));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({11, 1}, 2, 4));
    CompositeShape cs(rect);
    cs.addToArray(rect2);
    BOOST_CHECK(cs.getSlayers()(0,0) == rect);
  }
  
  BOOST_AUTO_TEST_CASE(TurnTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 4));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({10, 1}, 1, 1));
    CompositeShape cs(rect);

    cs.addToArray(rect2);
    cs.turn(90);
    rectangle_t frameRect = (*rect).getFrameRect();
    BOOST_CHECK(frameRect.pos.x == 5.25);
    BOOST_CHECK(frameRect.pos.y == -3.25);

    frameRect = (*rect2).getFrameRect();

    BOOST_CHECK(frameRect.pos.x == 5.25);
    BOOST_CHECK(frameRect.pos.y == 5.75);
  }

BOOST_AUTO_TEST_SUITE_END()
