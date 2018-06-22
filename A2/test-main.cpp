#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(TestCircle)

  BOOST_AUTO_TEST_CASE(ConstructorWrongParameter1)
  {
    Circle cir({1,1},-3.12213);
    BOOST_CHECK_CLOSE(cir.getRadius(),3.12213,0.001);
  }

  BOOST_AUTO_TEST_CASE(ConstructorWrongParameter2)
  {
    Circle cir({1,1},0);
    BOOST_CHECK_CLOSE(cir.getRadius(),1,0.001);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointRadiusConst)
  {
    point_t p={0,0};
    Circle cir({1,1},1);
    cir.move(p);
    BOOST_CHECK_CLOSE(cir.getRadius(),1,0.001);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointAreaConst)
  {
    point_t p={0,0};
    Circle cir({1,1},2.323231);
    cir.move(p);
    BOOST_CHECK_CLOSE(cir.getArea(),2.323231*2.323231*M_PI,0.001);
  }

  BOOST_AUTO_TEST_CASE(MoveByXYRadiusConst)
  {
    Circle cir({1,1},24.323231);
    cir.move(0,0);
    BOOST_CHECK_CLOSE(cir.getRadius(),24.323231,0.001);
  }

  BOOST_AUTO_TEST_CASE(MoveByXYAreaConst)
  {
    Circle cir({1,1},3);
    cir.move(0,0);
    BOOST_CHECK_CLOSE(cir.getArea(),9*M_PI,0.001);
  }

  BOOST_AUTO_TEST_CASE(ScaleAreaChange)
  {
    Circle cir({1,1},7);
    cir.scale(7);
    BOOST_CHECK_CLOSE(cir.getArea(),2401*M_PI,0.001);
  }

  BOOST_AUTO_TEST_CASE(ScaleCenerConst)
  {
    Circle cir({1,1},7);
    cir.scale(7);
    BOOST_CHECK_CLOSE(cir.getCenter().x,1,0.001);
    BOOST_CHECK_CLOSE(cir.getCenter().y,1,0.001);
  }

  BOOST_AUTO_TEST_CASE(ScaleWrongParametrer1)
  {
    Circle cir({1,1},3);
    cir.scale(-22.7);
    BOOST_CHECK_CLOSE(cir.getRadius(),68.1,0.001);
  }

  BOOST_AUTO_TEST_CASE(ScaleWrongParametrer2)
  {
    Circle cir({1,1},3);
    cir.scale(0);
    BOOST_CHECK_CLOSE(cir.getRadius(),3,0.001);
  }

  BOOST_AUTO_TEST_CASE(SetRadiusWrongParameter1)
  {
    Circle cir({1,1},3);
    cir.setRadius(21.9);
    BOOST_CHECK_CLOSE(cir.getRadius(),21.9,0.001);
  }

  BOOST_AUTO_TEST_CASE(SetRadiusWrongParameter2)
  {
    Circle cir({1,1},31.12);
    cir.setRadius(0);
    BOOST_CHECK_CLOSE(cir.getRadius(),1,0.001);
  }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(TestRectangle)

  BOOST_AUTO_TEST_CASE(ConstructorWrongParameter1)
  {
    Rectangle rect({1,1},-1,1);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width,1,0.001);
  }

  BOOST_AUTO_TEST_CASE(ConstructorWrongParameter2)
  {
    Rectangle rect({1,1},1,-1.31);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height,1.31,0.001);
  }

  BOOST_AUTO_TEST_CASE(ConstructorWrongParameter3)
  {
    Rectangle rect({1,1},1,0);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width,1,0.001);
  }

  BOOST_AUTO_TEST_CASE(ConstructorWrongParameter4)
  {
    Rectangle rect({1,1},0,1);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height,1,0.001);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointWidthConst)
  {
    point_t p={0,0};
    Rectangle rect({1,1},4.82,1);
    rect.move(p);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width,4.82,0.001);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointHeightConst)
  {
    point_t p={0,0};
    Rectangle rect({1,1},4.82,131.22);
    rect.move(p);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height,131.22,0.001);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointAreaConst)
  {
    point_t p={0,0};
    Rectangle rect({1,1},4,9);
    rect.move(p);
    BOOST_CHECK_CLOSE(rect.getArea(),36,0.001);
  }

  BOOST_AUTO_TEST_CASE(MoveByXYWidthConst)
  {
    Rectangle rect({1,1},24.82,1);
    rect.move(-1.1,0.9);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width,24.82,0.001);
  }

  BOOST_AUTO_TEST_CASE(MoveByXYHeightConst)
  {
    Rectangle rect({1,1},82,12.31);
    rect.move(-1.98,12);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height,12.31,0.001);
  }

  BOOST_AUTO_TEST_CASE(MoveByXYAreaConst)
  {
    Rectangle rect({1,1},2,9.1);
    rect.move(21,-32);
    BOOST_CHECK_CLOSE(rect.getArea(),18.2,0.001);
  }

  BOOST_AUTO_TEST_CASE(ScaleAreaChange)
  {
    Rectangle rect({1,1},2,2);
    rect.scale(2);
    BOOST_CHECK_CLOSE(rect.getArea(),16,0.001);
  }

  BOOST_AUTO_TEST_CASE(ScaleCenerConst)
  {
    Rectangle rect({1,1},2,2);
    rect.scale(2);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x,1,0.001);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y,1,0.001);
  }

  BOOST_AUTO_TEST_CASE(ScaleWrongParametrer1)
  {
    Rectangle rect({1,1},2,2);
    rect.scale(-322);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height,644,0.001);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width,644,0.001);
  }

  BOOST_AUTO_TEST_CASE(ScaleWrongParametrer2)
  {
    Rectangle rect({1,1},21,24);
    rect.scale(0);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height,24,0.001);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width,21,0.001); }

  BOOST_AUTO_TEST_CASE(SetHeightWrongParameter1)
  {
    Rectangle rect({1,1},2,2);
    rect.setHeight(-21.212);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height,21.212,0.001);
  }

  BOOST_AUTO_TEST_CASE(SetHeightrongParameter2)
  {
    Rectangle rect({1,1},0.2132,2);
    rect.setHeight(0);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height,1,0.001);
  }

  BOOST_AUTO_TEST_CASE(SetWidthtWrongParameter1)
  {
    Rectangle rect({1,1},2,2);
    rect.setWidth(-2.12);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width,2.12,0.001);
  }

  BOOST_AUTO_TEST_CASE(SetWidthtWrongParameter2)
  {
    Rectangle rect({1,1},2,2);
    rect.setWidth(0);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width,1,0.001);
  }

  BOOST_AUTO_TEST_CASE(TurnTest1)
  {
    Rectangle rect({1,1},2,4);
    rect.turn(90);
    BOOST_CHECK(rect.getVertex(0).x == -1);
    BOOST_CHECK(rect.getVertex(0).y == 0);

    BOOST_CHECK(rect.getVertex(1).x == -1);
    BOOST_CHECK(rect.getVertex(1).y == 2);

    BOOST_CHECK(rect.getVertex(2).x == 3);
    BOOST_CHECK(rect.getVertex(2).y == 2);

    BOOST_CHECK(rect.getVertex(3).x == 3);
    BOOST_CHECK(rect.getVertex(3).y == 0);
  }

  BOOST_AUTO_TEST_CASE(TurnTest2)
  {
    Rectangle rect({1,1},2,4);
    rect.turn(-90);
    BOOST_CHECK(rect.getVertex(0).x == -1);
    BOOST_CHECK(rect.getVertex(0).y == 0);

    BOOST_CHECK(rect.getVertex(1).x == -1);
    BOOST_CHECK(rect.getVertex(1).y == 2);

    BOOST_CHECK(rect.getVertex(2).x == 3);
    BOOST_CHECK(rect.getVertex(2).y == 2);

    BOOST_CHECK(rect.getVertex(3).x == 3);
    BOOST_CHECK(rect.getVertex(3).y == 0);
  }

  BOOST_AUTO_TEST_CASE(TurnTest3)
  {
    Rectangle rect({0,0},2,2);
    rect.turn(45);
    BOOST_CHECK_CLOSE(rect.getVertex(0).x, 0, 0.001);
    BOOST_CHECK_CLOSE(rect.getVertex(0).y, -sqrt(2), 0.001);

    BOOST_CHECK_CLOSE(rect.getVertex(1).x, -sqrt(2), 0.001);
    BOOST_CHECK_CLOSE(rect.getVertex(1).y, 0, 0.001);

    BOOST_CHECK_CLOSE(rect.getVertex(2).x, 0, 0.001);
    BOOST_CHECK_CLOSE(rect.getVertex(2).y, sqrt(2), 0.001);

    BOOST_CHECK_CLOSE(rect.getVertex(3).x, sqrt(2), 0.001);
    BOOST_CHECK_CLOSE(rect.getVertex(3).y, 0, 0.001);
  }

  BOOST_AUTO_TEST_CASE(MoveVertexesTest_Dx_Dy)
  {
    Rectangle rect({1,1},4,2);

    rect.move(2,2);

    BOOST_CHECK(rect.getVertex(0).x == 1);
    BOOST_CHECK(rect.getVertex(0).y == 2);

    BOOST_CHECK(rect.getVertex(1).x == 1);
    BOOST_CHECK(rect.getVertex(1).y == 4);

    BOOST_CHECK(rect.getVertex(2).x == 5);
    BOOST_CHECK(rect.getVertex(2).y == 4);

    BOOST_CHECK(rect.getVertex(3).x == 5);
    BOOST_CHECK(rect.getVertex(3).y == 2);
  }

  BOOST_AUTO_TEST_CASE(MoveVertexesTest_ToPoint)
  {
    Rectangle rect({1,1},4,2);

    point_t p = {3,3};

    rect.move(p);

    BOOST_CHECK(rect.getVertex(0).x == 1);
    BOOST_CHECK(rect.getVertex(0).y == 2);

    BOOST_CHECK(rect.getVertex(1).x == 1);
    BOOST_CHECK(rect.getVertex(1).y == 4);

    BOOST_CHECK(rect.getVertex(2).x == 5);
    BOOST_CHECK(rect.getVertex(2).y == 4);

    BOOST_CHECK(rect.getVertex(3).x == 5);
    BOOST_CHECK(rect.getVertex(3).y == 2);
  }

  BOOST_AUTO_TEST_CASE(getFrameRectTest)
  {
    Rectangle rect({0,0},2,5);
    rect.turn(90);
    rectangle_t frameRect = rect.getFrameRect();

    BOOST_CHECK(frameRect.height == 2);
    BOOST_CHECK(frameRect.width == 5);
  }

BOOST_AUTO_TEST_SUITE_END()
