#include <iterator>
#include <iostream>
#include <algorithm>
#include "analyze_data.h"

int main() {
  AnalyzeData analyzeData = std::for_each(std::istream_iterator<int>(std::cin),
                                          std::istream_iterator<int>(),
                                          AnalyzeData());
  if (!std::cin.eof()) {
    std::cerr << "Invalid input!";
    return 1;
  }
  analyzeData.print();
  return 0;
}

