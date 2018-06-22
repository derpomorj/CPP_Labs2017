#include <exception>
#include <iostream>
#include "task.hpp"

int main() {
  try {
    doTask();
  } catch (const std::exception &exception) {
    std::cerr << exception.what();
    return 1;
  }
  return 0;
}

