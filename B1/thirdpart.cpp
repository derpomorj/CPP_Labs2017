#include "impl.hpp"
#include <vector>

void tasks::doThirdPart(int argc)
{
  if (argc != 2) {
    throw std::invalid_argument("invalid number of parameters");
  }

  std::vector<int> vector = {};
  detail::readWithPushBack(vector);

  if (vector.empty()) {
    return;
  } else if (vector.back() != 0) {
    throw std::invalid_argument("missing zero");
  }
  vector.pop_back();

  if (vector.empty()) {
    return;
  }

  if (vector.back() == 1) {
    auto it = vector.begin();
    while (it != vector.end()) {
      if (*it % 2 == 0) {
        it = vector.erase(it);
      } else {
        it++;
      }
    }
  } else if (vector.back() == 2) {
    int multipleOf3 = 0;
    for (auto it = vector.begin(); it != vector.end(); it++) {
      if (*it % 3 == 0) {
        ++multipleOf3;
      }
    }
    vector.insert(vector.end(), multipleOf3 * 3, 0);
    for (auto it2 = vector.end() - 1, it1 = it2 - 3 * multipleOf3; it1 != it2; --it1, --it2) {
      if (*it1 % 3 == 0) {
        for (int i = 0; i < 3; ++i, --it2) {
          *it2 = 1;
        }
      }
      *it2 = *it1;
    }
  }
  detail::printCollection(vector, false);
}

