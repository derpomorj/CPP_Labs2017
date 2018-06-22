#ifndef B2_FormatText_HPP
#define B2_FormatText_HPP

#include <iostream>
#include <string>

  class TextFormatter {
    public:
    explicit TextFormatter(const size_t bufferSize = 40, std::istream *input = &std::cin);
    ~TextFormatter();
    void formatText();

    private:
    std::string buffer_;
    std::istream *input_;
    char lastChar_;
    size_t bufferMaxSize_;

    void readNumber(std::string &tempString);
    void readWord(std::string &tempString);
    void readDash(std::string &tempString);
    void skipWs();
  };

#endif //B2_FormatText_HPP

