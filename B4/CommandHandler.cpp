#include "CommandHandler.hpp"
#include <istream>
#include <sstream>
#include <iostream>
#include <algorithm>

CommandHandler::CommandHandler(PhoneBook* phoneBook, std::istream* input):
  phoneBookPtr_(phoneBook),
  bookmarks_(),
  input_(input),
  currentLine(),
  ok_(true)
{
  bookmarks_.insert(bookmarks_.begin(),{"current",phoneBook->begin()});
}

void CommandHandler::operator()() {
  while (!((*input_ >> std::ws).eof())) {
    ok_ = true;
    std::string command;
    std::getline(*input_, command);
    currentLine.clear();
    currentLine.str(command);
    std::getline(currentLine, command, ' ');
    if (currentLine.eof()) {
      invalidHandler(COMMAND_ERROR);
    } else if (command == "add") {
      insertBackHandler();
    } else if (command == "insert") {
      insertHandler();
    } else if (command == "delete") {
      deleteHandler();
    } else if (command == "show") {
      showHandler();
    } else if (command == "move") {
      moveHandler();
    } else if (command == "store") {
      storeHandler();
    } else {
      invalidHandler(COMMAND_ERROR);
    }
  }
}

std::function<bool(char)> CommandHandler::checkMarkCondition = [](char c) {
  return (std::isalnum(c)) || (c == '-');
};

std::function<bool(char)> CommandHandler::checkNumberCondition = [](char c) {
  return (std::isdigit(c));
};

user_t CommandHandler::readUserData() {
  std::string number(readWord(checkNumberCondition, COMMAND_ERROR));
  std::string name;
  if (!((currentLine >> std::ws).eof()) && (ok_)) {
    char c = {};
    currentLine >> c;
    if (c == '\"') {
      std::getline(currentLine,name,'\"');
      if (name.empty()){
        invalidHandler(COMMAND_ERROR);
        return {};
      }
      while (!(currentLine.eof()) && (name.back() =='\\'))
      {
        name.back() = '\"';
        std::string tempString;
        std::getline(currentLine,tempString,'\"');
        name.append(tempString);
      }
      currentLine.unget();
      currentLine >> c;
      if (!(currentLine >> std::ws).eof() || (c != '\"')){
        invalidHandler(COMMAND_ERROR);
      }
    } else {
      invalidHandler(COMMAND_ERROR);
    }
  }
  return {name,number};
}

void CommandHandler::insertBackHandler() {
  user_t user = readUserData();
  if (ok_) {
    if (phoneBookPtr_->empty()) {
      phoneBookPtr_->pushBack(user);
      bookmarks_.find("current")->second = phoneBookPtr_->begin();
    } else {
      phoneBookPtr_->pushBack(user);
    }
  }
}

void CommandHandler::storeHandler() {
  auto bookMarkIterator(readBookmarkIterator());
  std::string newMark(readWord(checkMarkCondition, BOOKMARK_ERROR));
  if (ok_) {
    std::pair<std::string, std::list<std::list<user_t>::iterator>::iterator&> myMark(newMark, bookMarkIterator->second);
    bookmarks_.insert(myMark);
  }
}


void CommandHandler::insertHandler() {
  std::string pos;
  std::getline(currentLine, pos, ' ');
  if (pos == "before") {
    insertWithMarkHandler(true);
  } else if (pos == "after") {
    insertWithMarkHandler(false);
  } else {
    invalidHandler(COMMAND_ERROR);
  }
}

void CommandHandler::insertWithMarkHandler(const bool insertBeforeMark) {
  auto bookMarkIterator(readBookmarkIterator());
  user_t user = readUserData();
  if (ok_) {
    if (phoneBookPtr_->empty()) {
      phoneBookPtr_->pushBack(user);
      bookmarks_.find("current")->second = phoneBookPtr_->begin();
    } else {
      phoneBookPtr_->insert(user, bookMarkIterator->second, insertBeforeMark);
    }
  }
}


void CommandHandler::deleteHandler() {
  auto bookMarkIterator(readBookmarkIterator());
  if (ok_) {
    for (auto it = bookmarks_.begin(); it != bookmarks_.end(); ++it){
      if (it != bookMarkIterator && it->second == bookMarkIterator->second) {
        if (it->second == --phoneBookPtr_->end()) {
          --(it->second);
        } else {
          ++(it->second);
        }
      }
    }
    (bookMarkIterator->second) = phoneBookPtr_->removeElement(bookMarkIterator->second);
  }
}

void CommandHandler::showHandler() {
  auto bookMarkIterator(readBookmarkIterator());
  if (ok_) {
    phoneBookPtr_->show(bookMarkIterator->second);
  }
}

void CommandHandler::moveHandler() {
  auto bookMarkIterator(readBookmarkIterator());
  if (ok_) {
    std::string step;
    char c = 0;
    currentLine >> c;
    if (c == 'f' || c == 'l') {
      currentLine.unget();
      std::getline(currentLine, step, ' ');
      if (step == "first") {
        bookMarkIterator->second = phoneBookPtr_->begin();
      } else if (step == "last") {
        bookMarkIterator->second = (--phoneBookPtr_->end());
      }
    } else {
      if (c == '-' || c == '+') {
        step.push_back(c);
      } else {
        currentLine.unget();
      }
      step += readWord(checkNumberCondition, STEP_ERROR);
      if (!(currentLine >> std::ws).eof() || !ok_) {
        invalidHandler(COMMAND_ERROR);
        return;
      }
      try {
        phoneBookPtr_->advance(bookMarkIterator->second, std::stoi(step));
      } catch (std::out_of_range) {
        invalidHandler(STEP_ERROR);
      }
    }
  }
}

void CommandHandler::invalidHandler(ERROR er) {
  if (ok_) {
    ok_ = false;
    if (er == 0) {
      std::cout << "<INVALID COMMAND>\n";
    } else if (er == 1) {
      std::cout << "<INVALID BOOKMARK>\n";
    } else if (er == 2) {
      std::cout << "<INVALID STEP>\n";
    }
  }
}

CommandHandler::BookmarkContainerType::iterator CommandHandler::readBookmarkIterator() {
  std::string mark(readWord(checkMarkCondition, BOOKMARK_ERROR));
  if (!mark.empty() && ok_) {
    auto it = bookmarks_.find(mark);
    if (it == bookmarks_.end()) {
      invalidHandler(BOOKMARK_ERROR);
    }
    return it;
  }
  invalidHandler(BOOKMARK_ERROR);
  return {};
}

std::string
CommandHandler::readWord(const std::function<bool(char)> &checkConditions, ERROR error) {
  if (currentLine.eof()) {
    invalidHandler(COMMAND_ERROR);
    return {};
  }
  std::string word;
  std::getline(currentLine, word, ' ');
  for (const char &i : word) {
    if (!checkConditions(i)) {
      invalidHandler(error);
      return {};
    }
  }
  return word;
}


