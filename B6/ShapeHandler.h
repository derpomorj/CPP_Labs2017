#ifndef B6_SHAPEHANDLER_H
#define B6_SHAPEHANDLER_H

#include <vector>
#include <sstream>
#include <unordered_map>

struct Point
{
  int x, y;
};

using Shape = std::vector<Point>;

enum class ShapeType {
  TRIANGLE,
  SQUARE,
  RECTANGLE,
  ANOTHER
};

struct ShapeInfo {
  ShapeType shapeType;
  int vertex;
};

struct ShapeCompare {
  bool operator()(const std::pair<ShapeInfo,Shape> &lhs, const std::pair<ShapeInfo,Shape>  &rhs) const {
    if (lhs.first.vertex == rhs.first.vertex) {
      return lhs.first.shapeType < rhs.first.shapeType;
    }
    return lhs.first.vertex < rhs.first.vertex;
  }
};

struct PointCompare {
  bool operator()(const Point &lhs, const Point &rhs) const {
    if (lhs.x == rhs.x) {
      return lhs.y < rhs.y;
    }
    return lhs.x < rhs.x;
  }
};

class ShapeHandler {
public:
  ShapeHandler();
  void operator()(std::istream&);

  int getVertexNumber() const;
  int getTrianglesNumber() const;
  int getSquaresNumber() const;
  int getRectanglesNumber() const;

private:
  std::vector<std::pair<ShapeInfo,Shape>> shapeContainer_;
  std::vector<Point> resultPoints_;
  std::istringstream line_;
  int vertexNumber_;
  int triangleNumber_;
  int squareNumber_;
  int rectangleNumber_;

  ShapeInfo getShapeInfo (Shape&, int);
  void getShape();
  Point getPoint();
  void printResults();

};

#endif

