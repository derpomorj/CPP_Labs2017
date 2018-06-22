#include "tasks.hpp"
#include "CommandHandler.hpp"

void doFirstPart() {
  QueueWithPriority<std::string> queue;
  CommandHandler handler(queue);
  handler(&std::cin);
}

