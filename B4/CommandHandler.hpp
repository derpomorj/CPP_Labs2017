#ifndef B4_COMMANDHANDLER_HPP
#define B4_COMMANDHANDLER_HPP

#include <functional>
#include <sstream>
#include <map>
#include <list>
#include "user.hpp"
#include "PhoneBook.hpp"

class CommandHandler {
  public:
  using BookmarkContainerType = std::map<std::string,std::list<std::list<user_t>::iterator>::iterator>;
  explicit CommandHandler(PhoneBook*, std::istream*);
  void operator()();
  private:
  enum  ERROR {
    COMMAND_ERROR,
    BOOKMARK_ERROR,
    STEP_ERROR
  };
  PhoneBook* phoneBookPtr_;
  BookmarkContainerType bookmarks_;
  std::istream* input_;
  std::istringstream currentLine;
  bool ok_;

  user_t readUserData();
  std::string readWord(const std::function<bool(char)> &, ERROR);
  BookmarkContainerType::iterator readBookmarkIterator();

  static std::function<bool(char)> checkMarkCondition;
  static std::function<bool(char)> checkNumberCondition;

  void storeHandler();
  void insertHandler();
  void insertBackHandler();
  void insertWithMarkHandler(bool insertAfterMark);
  void deleteHandler();
  void showHandler();
  void moveHandler();
  void invalidHandler(ERROR);
};


#endif //B4_COMMANDHANDLER_HPP

