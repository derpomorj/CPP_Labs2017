#include "tasks.hpp"
#include <iostream>
#include "CommandHandler.hpp"

void doFirstPart(){
  PhoneBook phoneBook;
  CommandHandler handler(&phoneBook,&std::cin);
  handler();
}


