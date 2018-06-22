#include "tasks.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
  if (argc == 1) {
    std::cerr << "invalid input arguments";
    return 1;
  }

  try {
    switch (std::stoi(argv[1])) {
      case 1: {
        tasks::doFirstPart(argc, argv);
        break;
      }
      case 2: {
        tasks::doSecondPart(argc, argv);
        break;
      }
      case 3: {
        tasks::doThirdPart(argc);
        break;
      }
      case 4: {
        tasks::doFourthPart(argc, argv);
        break;
      }
      default: {
        std::cerr << "invalid input arguments";
        return 1;
      }
    }
  }
  catch (const std::exception& exception) {
    std::cerr << exception.what();
    return 1;
  }
  return 0;
}
