#include "tasks.h"
#include <unordered_set>
#include <iostream>
#include <iterator>

void doFirstPart()
{
  std::unordered_set<std::string> words{std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>()};

  std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

