#ifndef B5_TASK_HPP
#define B5_TASK_HPP

#include <iostream>
#include <iterator>
#include <algorithm>
#include "impl.hpp"

void doTask(){
  std::vector<DataStruct> vector = {};
  readDataStruct(vector);
  std::sort(vector.begin(),vector.end());
  std::copy(vector.begin(),vector.end(),std::ostream_iterator<DataStruct>(std::cout));
}

#endif

