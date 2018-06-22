#include "CommandHandler.hpp"
#include <sstream>

CommandHandler::CommandHandler(QueueWithPriority<std::string>& queue):
queue_(queue)
{}

void CommandHandler::operator()(std::istream* input) {
  while (!((*input >> std::ws).eof())) {
    std::string command;
    std::getline(*input, command);
    if (command == "get") {
      getHandler();
    } else if (command == "accelerate") {
      accelerateHandler();
    } else {
      addHandler(command);
    }
  }
}

void CommandHandler::addHandler(std::string& command) {
  std::istringstream commandLine(command);
  std::getline(commandLine, command, ' ');
  std::string strPriority;
  std::getline(commandLine, strPriority, ' ');
  if ((command != "add") || (commandLine.eof())) {
    invalidHandler();
    return;
  }
  std::string data;
  if (strPriority == "low") {
    std::getline(commandLine, data);
    queue_.putToQueue(data, queue_.LOW);
  } else if (strPriority == "normal") {
    std::getline(commandLine, data);
    queue_.putToQueue(data, queue_.NORMAL);
  } else if (strPriority == "high") {
    std::getline(commandLine, data);
    queue_.putToQueue(data, queue_.HIGH);
  } else {
    invalidHandler();
  }
}

void CommandHandler::getHandler() {
  if (queue_.printNextEl()) {
    queue_.popFromQueue();
  }
}

void CommandHandler::accelerateHandler() {
  queue_.accelerate();
}

void CommandHandler::invalidHandler() const {
  std::cout << "<INVALID COMMAND>\n";
}

