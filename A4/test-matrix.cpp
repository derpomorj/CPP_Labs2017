#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "compositeshape.hpp"
#include "matrixshape.hpp"

BOOST_AUTO_TEST_SUITE(MatrixShapeTest)

  BOOST_AUTO_TEST_CASE(ConstructorWrongParameterTest)
  {
    std::shared_ptr<Shape> rect = nullptr;
    BOOST_CHECK_THROW(MatrixShape ms(rect), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(CopyConstructorTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 4));
    MatrixShape ms(rect);
    MatrixShape ms2(ms);
    BOOST_CHECK(ms(0,0) == ms2(0,0));
  }

  BOOST_AUTO_TEST_CASE(MoveConstructorTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 4));
    MatrixShape ms(rect);
    MatrixShape ms2(std::move(ms));
    BOOST_CHECK_THROW(ms(0,0), std::out_of_range);
    BOOST_CHECK(ms2(0,0) == rect);
    BOOST_CHECK(rect.use_count() == 2);
  }

  BOOST_AUTO_TEST_CASE(CopyOperatorTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 4));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({11, 1}, 2, 4));
    MatrixShape ms(rect);
    MatrixShape ms2(rect2);
    ms2 = ms;
    BOOST_CHECK(ms(0,0) == ms2(0,0));
  }

  BOOST_AUTO_TEST_CASE(BracketsTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 4));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({11, 1}, 2, 4));
    MatrixShape ms(rect);
    ms.addToMatrix(rect2);
    BOOST_CHECK(ms(0,0) == rect);
    BOOST_CHECK(ms(0,1) == rect2);
  }

  BOOST_AUTO_TEST_CASE(BracketsWrongParameterTest)
  {
    MatrixShape ms;
    BOOST_CHECK_THROW(ms(0,0), std::out_of_range);
  }


  BOOST_AUTO_TEST_CASE(MoveOperatorTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 4));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({11, 1}, 2, 4));
    MatrixShape ms(rect);
    MatrixShape ms2(rect2);
    ms2 = std::move(ms);
    BOOST_CHECK_THROW(ms(0,0), std::out_of_range);
    BOOST_CHECK(ms2(0,0) == rect);
    BOOST_CHECK(rect2.use_count() == 1);
  }

  BOOST_AUTO_TEST_CASE(AddToMatrixTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 4));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({10, 1}, 2, 4));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({10, 1}, 1, 4));
    MatrixShape ms(rect);
    ms.addToMatrix(rect2);
    ms.addToMatrix(rect3);
    BOOST_CHECK(ms(0,1) == rect2);
    BOOST_CHECK(ms(1,0) == rect3);
  }

  BOOST_AUTO_TEST_CASE(AddToMatrixTestWrongParameter)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 4));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({10, 1}, 2, 4));
    std::shared_ptr<Shape> rect3 = nullptr;
    MatrixShape ms(rect);
    BOOST_CHECK_THROW(ms.addToMatrix(rect3), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(AddToMatrixTestWrongParameter2)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 4));
    MatrixShape ms(rect);
    BOOST_CHECK_THROW(ms.addToMatrix(rect), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(CheckInsertionTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle({1, 1}, 2, 4));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({0, 1}, 2, 4));
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({10, 1}, 2, 4));
    MatrixShape ms;
    BOOST_CHECK(ms.checkIntersection(rect , rect2));
    BOOST_CHECK(!ms.checkIntersection(rect , rect3));
  }

  BOOST_AUTO_TEST_CASE(CheckInsertionWrongParametrTest)
  {
    std::shared_ptr<Shape> rect = nullptr;
    MatrixShape ms;
    BOOST_CHECK_THROW(ms.checkIntersection(rect , rect), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
