#include "impl.hpp"
#include <vector>
#include <forward_list>

void tasks::doFirstPart(int argc, char* argv[])
{
  if (argc != 3) {
    throw std::invalid_argument("invalid number of parameters");
  }
  auto comparator = detail::setSortDirection<int>(argv[2]);

  std::vector<int> vectorA = {};
  detail::readWithPushBack(vectorA);

  if (vectorA.empty()) {
    return;
  }

  std::vector<int> vectorB = vectorA;
  std::forward_list<int> fList(vectorA.begin(),vectorA.end());

  detail::sort<detail::AccessByBrackets>(vectorA,comparator);
  detail::printCollection(vectorA);

  detail::sort<detail::AccessByAt>( vectorB, comparator);
  detail::printCollection(vectorB);

  detail::sort<detail::AccessByIterator>(fList, comparator);
  detail::printCollection(fList,false);
}

