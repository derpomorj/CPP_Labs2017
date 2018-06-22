#include "factorialContainer.hpp"

factorialIterator factorialContainer::begin() {
  return factorialIterator(1);
}

factorialIterator factorialContainer::end() {
  return factorialIterator(11);
}

