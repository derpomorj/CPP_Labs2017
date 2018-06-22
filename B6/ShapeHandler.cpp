#include <sstream>
#include <algorithm>
#include <iostream>
#include "ShapeHandler.h"

ShapeHandler::ShapeHandler():
  shapeContainer_(),
  resultPoints_(),
  line_(),
  vertexNumber_(),
  triangleNumber_(),
  squareNumber_(),
  rectangleNumber_()
{
  line_.exceptions(std::istringstream::failbit | std::istringstream::badbit);
}

void ShapeHandler::operator()(std::istream& in) {
  while (!(in >> std::ws).eof()) {
    std::string string;
    std::getline(in, string);
    line_.clear();
    line_.str(string);
    getShape();
  }
  std::for_each(shapeContainer_.begin(), shapeContainer_.end(), [this](const std::pair<ShapeInfo, Shape> &element) {
    vertexNumber_ += element.first.vertex;
    if (element.first.shapeType == ShapeType::TRIANGLE) {
      ++triangleNumber_;
    } else if (element.first.shapeType == ShapeType::SQUARE) {
      ++squareNumber_;
      ++rectangleNumber_;
    } else if (element.first.shapeType == ShapeType::RECTANGLE) {
      ++rectangleNumber_;
    }
    if (element.first.vertex != 5) {
      resultPoints_.push_back(element.second[0]);
    }
  });
  shapeContainer_.erase(std::remove_if(shapeContainer_.begin(),
                                       shapeContainer_.end(),
                                       [](const std::pair<ShapeInfo, Shape> &element) {
                                         return (element.first.vertex == 5);
                                       }),
                        shapeContainer_.end());
  std::sort(shapeContainer_.begin(),shapeContainer_.end(),ShapeCompare());
  printResults();
}

ShapeInfo ShapeHandler::getShapeInfo(Shape & shape, int vertexes) {
  if (vertexes == 3) {
    return {ShapeType::TRIANGLE, vertexes};
  } else if (vertexes == 4) {
    auto tempShape = shape;
    std::sort(tempShape.begin(), tempShape.end(), PointCompare());
    if ((tempShape[1].x - tempShape[0].x) * (tempShape[3].x - tempShape[1].x)
        + (tempShape[1].y - tempShape[0].y) * (tempShape[3].y - tempShape[1].y) == 0
        && (tempShape[3].x - tempShape[1].x) * (tempShape[2].x - tempShape[3].x)
           + (tempShape[3].y - tempShape[1].y) * (tempShape[2].y - tempShape[3].y) == 0
        && (tempShape[0].x - tempShape[2].x) * (tempShape[1].x - tempShape[0].x)
           + (tempShape[0].y - tempShape[2].y) * (tempShape[1].y - tempShape[0].y) == 0) {
      if ((tempShape[1].x - tempShape[0].x) * (tempShape[1].x - tempShape[0].x)
          + (tempShape[1].y - tempShape[0].y) * (tempShape[1].y - tempShape[0].y)
          == (tempShape[3].x - tempShape[1].x) * (tempShape[3].x - tempShape[1].x)
             + (tempShape[3].y - tempShape[1].y) * (tempShape[3].y - tempShape[1].y)) {
        return {ShapeType::SQUARE, vertexes};
      }
      return {ShapeType::RECTANGLE, vertexes};
    }
  }
  return {ShapeType::ANOTHER, vertexes};
}

int ShapeHandler::getVertexNumber() const {
  return vertexNumber_;
}

int ShapeHandler::getTrianglesNumber() const {
  return triangleNumber_;
}

int ShapeHandler::getSquaresNumber() const {
  return squareNumber_;
}

int ShapeHandler::getRectanglesNumber() const {
  return rectangleNumber_;
}

void ShapeHandler::getShape() {
  Shape shape;
  int vertexes = 0;
  line_ >> vertexes;
  for (int i = 0; i < vertexes; ++i){
    shape.push_back(getPoint());
  }
  if (!((line_ >> std::ws).eof())){
    throw std::invalid_argument("invalid number of points");
  }
  shapeContainer_.push_back({getShapeInfo(shape,vertexes),shape});
}

Point ShapeHandler::getPoint() {
  if (line_.eof()){
    throw std::invalid_argument("invalid number of points");
  }
  char open_bracket = 0;
  char close_bracket = 0;
  char delimeter = 0;
  Point point = {0,0};
  line_ >> std::skipws >> open_bracket >> point.x >> std::ws
        >> delimeter >> point.y >> close_bracket;
  if (open_bracket != '(' || delimeter != ';' || close_bracket != ')'){
    throw std::invalid_argument("invalid point!");
  }
  return point;
}

std::ostream& operator <<(std::ostream& os, const std::vector<Point>& points){
  for (auto point : points) {
    os << "(" << point.x << ";" << point.y << ") ";
  }
  return os;
}

void ShapeHandler::printResults() {
  std::cout << "Vertices: " << vertexNumber_ << "\nTriangles: " << triangleNumber_
            << "\nSquares: " << squareNumber_ << "\nRectangles: " << rectangleNumber_
            << "\nPoints: " << resultPoints_ << "\nShapes:\n";
  for (auto it = shapeContainer_.begin(); it != shapeContainer_.end(); ++it) {
    std::cout << it->first.vertex << " " << it->second << "\n";
  }
}


