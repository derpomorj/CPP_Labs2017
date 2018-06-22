#include <cstring>
#include "impl.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "invalid input!";
    return 1;
  } else {
    try {
      if (std::strcmp(argv[1], "1") == 0) {
        doFirstPart();
        return 0;
      } else if (std::strcmp(argv[1], "2") == 0) {
        doSecondPart();
        return 0;
      } else {
        std::cerr << "invalid input!";
        return 1;
      }
    } catch (const std::exception &exception) {
      std::cerr << exception.what() << "\n";
      return 1;
    }
    return 0;
  }
}
