#include "TextFormatter.hpp"

int main(int argc, char** argv) {
  try {
    if ((argc > 3) || (argc == 2)) {
      throw std::invalid_argument("Wrong number of options");
    }

    int width = 40;
    const int min_width = 25;

    if (argc == 3) {
      width = std::atoi(argv[2]);
      if (std::string(argv[1]) != "--line-width") {
        throw std::invalid_argument("Not correct option");
      }

      if (width < min_width) {
        throw std::invalid_argument("line width must be greater than 25");
      }
    }
    TextFormatter formatter(width);
    formatter.formatText();

  } catch (const std::exception &exception) {
    std::cerr << exception.what() << '\n';
    return 1;
  }

  return 0;
}


