#include "TextFormatter.hpp"
#include <iterator>

TextFormatter::TextFormatter(const size_t bufferSize, std::istream *input):
  buffer_(),
  input_(input),
  lastChar_(' '),
  bufferMaxSize_(bufferSize)
{
  buffer_.reserve(bufferSize);
}

TextFormatter::~TextFormatter() {
  if (!buffer_.empty()) {
    std::cout << buffer_ <<"\n";
  }
}

void TextFormatter::formatText() {
  if (input_ == nullptr) {
    return;
  }
  std::string tempString;
  tempString.reserve(26);
  while (input_->get(lastChar_)) {
    if (std::isspace(lastChar_, input_->getloc())) {
      continue;
    } else if (std::isdigit(lastChar_, input_->getloc()) || lastChar_ == '+' || lastChar_ == '-') {
      tempString.push_back(lastChar_);
      readNumber(tempString);
    } else if (std::isalpha(lastChar_, input_->getloc())) {
      tempString.push_back(lastChar_);
      readWord(tempString);
    } else if (std::ispunct(lastChar_, input_->getloc())) {
      throw std::invalid_argument("Wrong punctuation!");
    }
    if (bufferMaxSize_ - buffer_.size() <= tempString.size()) {
      std::cout << buffer_ <<"\n";
      buffer_.clear();
    } else if ((buffer_.size() + tempString.size() < bufferMaxSize_ + 1) && !(buffer_.empty())) {
      buffer_.push_back(' ');
    }

    buffer_ += tempString;

    tempString.clear();
  }
}


void TextFormatter::readNumber(std::string& tempString) {
  size_t counter = 1;
  char decimal_point = std::use_facet<std::numpunct<char>>(input_->getloc()).decimal_point();
  while (input_->get(lastChar_)) {
    if (!std::isdigit(lastChar_, input_->getloc())) {
      if ((tempString == "-") || (tempString == "+")) {
        throw std::invalid_argument("Wrong input!");
      }
      if (std::isspace(lastChar_, input_->getloc())) {
        skipWs();
      } else if (lastChar_ == decimal_point) {
        if (tempString.find(decimal_point) == tempString.npos) {
          ++counter;
          tempString.push_back(lastChar_);
          continue;
        }
      }
      if (std::ispunct(lastChar_, input_->getloc())) {
        if (tempString.back() == decimal_point) {
          throw std::invalid_argument("Wrong input!");
        }
        switch (lastChar_) {
        case '+':
          break;
        case ',':
            tempString.push_back(lastChar_);
            input_->get(lastChar_);
            skipWs();
            if (lastChar_ != '-') {
              break;
            }
        case '-':
        {
          char nextChar = input_->peek();
          if (nextChar == '-') {
            readDash(tempString);
            return;
          } else {
            break;
          }
        }
        default:
          tempString.push_back(lastChar_);
          return;
        }
      }
      input_->unget();
      return;
    }
    if (++counter > 20) {
      throw std::invalid_argument("out of Number Size!");
    }
    tempString.push_back(lastChar_);
  }
  if ((tempString == "-") || (tempString == "+")) {
    throw std::invalid_argument("wrong input!");
  }
}

void TextFormatter::readWord(std::string& tempString) {
  size_t counter = 1;
  while (input_->get(lastChar_)) {
    if (!std::isalpha(lastChar_, input_->getloc())) {
      if (lastChar_ == '-') {
        if (tempString.back() == '-') {
          readDash(tempString);
          return;
        } else {
          ++counter;
          tempString.push_back(lastChar_);
          continue;
        }
      }
      if (std::isspace(lastChar_, input_->getloc())) {
        skipWs();
          if (lastChar_ == '-') {
            readDash(tempString);
            return;
          }
        }
      if (std::ispunct(lastChar_, input_->getloc())) {
        tempString.push_back(lastChar_);
        if (lastChar_ == ',') {
          input_->get(lastChar_);
          skipWs();
          if (lastChar_ == '-') {
            readDash(tempString);
            return;
          }
        } else {
          return;
        }
      }
      input_->unget();
      return;

    }

    if (++counter > 20) {
      throw std::invalid_argument("out of Word Size!");
    }

    tempString.push_back(lastChar_);
  }
}

void TextFormatter::readDash(std::string &tempString) {
  std::string dash(1, '-');
  dash.reserve(4);
  if (tempString.back() == '-') {
    dash.push_back('-');
  }
  for (int i = 0; (i < 2) && (input_); ++i) {
    input_->get(lastChar_);
    dash.push_back(lastChar_);
  }
  if (dash.back() != '-') {
    input_->unget();
    dash.pop_back();
  }
  if (dash == "---") {
    if (tempString.back() == '-') {
      tempString.back() = ' ';
      tempString.append("---");
      return;
    } else {
      tempString.append(" ---");
      return;
    }
  } else if (dash == "----") {
    tempString.append(" ---");
    return;
  }
  throw std::invalid_argument("invalid Dash!");
}

void TextFormatter::skipWs() {
  while (std::isspace(lastChar_, input_->getloc()) && !(input_->eof())) {
    input_->get(lastChar_);
  }
}

