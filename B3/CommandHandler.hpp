#ifndef B3_COMMANDHANDLER_HPP
#define B3_COMMANDHANDLER_HPP

#include "QueueWithPriority.hpp"

class CommandHandler {
  public:
  explicit CommandHandler(QueueWithPriority<std::string> &queue);

  void operator()(std::istream* istream);

  private:
  QueueWithPriority<std::string> queue_;

  void addHandler(std::string& command);
  void getHandler();
  void accelerateHandler();
  void invalidHandler() const;
};

#endif

