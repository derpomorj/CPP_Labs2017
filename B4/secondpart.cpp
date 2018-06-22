#include "tasks.hpp"
#include <iostream>
#include <algorithm>
#include "factorialContainer.hpp"

void doSecondPart(){
  factorialContainer container;
  std::copy(container.begin(),container.end(),std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';
  std::reverse_copy(container.begin(),container.end(),std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';
}

