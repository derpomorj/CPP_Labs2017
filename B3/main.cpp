#include <iostream>
#include "tasks.hpp"

int main(int argc, char** argv) {
  try {
    if (argc != 2) {
      throw std::invalid_argument("Wrong number of arguments!");
    }
    std::string parametr(argv[1]);
    if (parametr == "1") {
      doFirstPart();
    } else if (parametr == "2") {
      doSecondPart();
    } else {
      throw std::invalid_argument("Invalid argument!");
    }
  } catch (const std::exception &exception) {
    std::cerr << exception.what();
    return 1;
  }
  return 0;
}

