#include <iostream>
#include <cstring>
#include "tasks.hpp"


int main(int argc, char** argv) {
  try{
    if (argc != 2){
      throw std::invalid_argument("wrong number of arguments!");
    }
    if(std::strcmp(argv[1], "1") == 0)
    {
      doFirstPart();
    }
    else if(std::strcmp(argv[1], "2") == 0)
    {
      doSecondPart();
    } else {
      throw std::invalid_argument("invalid arguments");
    }

  } catch (const std::exception& exception) {
    std::cerr << exception.what();
    return 2;
  }
  return 0;
}

