#include "tasks.hpp"
#include <list>
#include <iterator>
#include <iostream>

void doSecondPart() {
  std::list<int> list(std::istream_iterator<int>(std::cin), std::istream_iterator<int>());

  if (!(std::cin.eof())) {
    throw std::invalid_argument("Wrong input!");
  }
  if (list.empty()) {
    return;
  }
  if (list.size() > 20) {
    throw std::invalid_argument("Wrong input!");
  }
  for (auto it = list.begin(); it != list.end(); ++it) {
    if ((*it < 1) || (*it > 20)) {
      throw std::invalid_argument("Wrong input!");
    }
  }
  for (auto it1 = list.begin(), it2 = list.end(); it1 != it2--; it1++) {
    if (it1 == it2) {
      std::cout << *it1 << "\n";
      return;
    }
    std::cout << *it1 << " " << *it2 << " ";
  }

  std::cout << "\n";
}

