#include <exception>
#include <iostream>
#include <cstring>
#include "tasks.h"

int main(int argc,char** argv) {

  if (argc != 2) {
    std::cerr << "Invalid number of parameters!";
    return 1;
  }
  try {
    if (std::strcmp(argv[1], "1") == 0) {
      doFirstPart();
    } else if (std::strcmp(argv[1], "2") == 0) {
      doSecondPart();
    } else {
      std::cerr << "Invalid parametrs " << std::string(argv[1]);
      return 1;
    }
  } catch (const std::exception &exception) {
    std::cerr << exception.what();
    return 1;
  }
  return 0;
}

