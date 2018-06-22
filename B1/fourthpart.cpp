#include "impl.hpp"
#include <ctime>
#include <vector>

void detail::fillRandom(double * array, int size)
{
  if (array == nullptr){
    throw std::invalid_argument("invalid argument");
  }
  srand(time(0));
  for (int i = 0; i < size; ++i) {
    array[i] = (static_cast<double>(rand()) / (RAND_MAX)) * 2 - 1.0;
  }
}

void tasks::doFourthPart(int argc, char* argv[])
{
  if (argc != 4) {
    throw std::invalid_argument("invalid number of parameters");
  }

  int sizeOfArray = std::stoi(argv[3]);

  if (sizeOfArray == 0){
    return;
  }

  std::vector<double> vector(sizeOfArray);
  detail::fillRandom(vector.data(), sizeOfArray);

  detail::printCollection(vector);
  detail::sort<detail::AccessByBrackets>(vector,detail::setSortDirection<double>(argv[2]));
  detail::printCollection(vector,false);
}

