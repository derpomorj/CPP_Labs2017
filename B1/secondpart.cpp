#include "impl.hpp"
#include <fstream>
#include <memory>
#include <vector>

void tasks::doSecondPart(int argc, char* argv[])
{
  if (argc != 3) {
    throw std::invalid_argument("invalid number of parameters");
  }

  std::ifstream inputFile(argv[2]);

  if (!inputFile.is_open()) {
    throw std::invalid_argument("invalid filename");
  }

  inputFile.seekg(0, inputFile.end);
  auto length = inputFile.tellg();

  inputFile.seekg(0, inputFile.beg);
  std::unique_ptr<char[]> buffer(std::make_unique<char[]>(length));

  inputFile.read(buffer.get(), length);

  inputFile.close();
  if (inputFile.is_open()) {
    throw std::ios_base::failure("cant close the file");
  }
  std::vector<char> vector(buffer.get(), buffer.get() + length);
  detail::printCollection(vector, false, false);
}

