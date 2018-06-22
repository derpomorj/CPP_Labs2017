#include "impl.hpp"
#include <iostream>
#include <sstream>

void readDataStruct(std::vector<DataStruct>& vector) {
  while (!(std::cin >> std::ws).eof()) {
    DataStruct dataStruct = {};
    std::string line;
    std::getline(std::cin,line);
    std::istringstream currentLine(line);
    dataStruct.key1 = readKey(currentLine);
    dataStruct.key2 = readKey(currentLine);
    currentLine >> std::ws;
    std::getline(currentLine,dataStruct.str);
    if (dataStruct.str.empty()){
      throw std::invalid_argument("invalid argument");
    }
    vector.push_back(dataStruct);
  }
}

int readKey(std::istringstream& line){
  int key = 0;
  line >> key;
  if ((key >5) || (key < -5)){
    throw std::invalid_argument("invalid argument!");
  }
  std::string str{};
  std::getline(line,str,',');
  if (!str.empty() || line.eof()){
    throw std::invalid_argument("invalid argument");
  }
  return key;
}

std::ostream& operator << (std::ostream &s, const DataStruct& dataStruct)
{
  s << dataStruct.key1 << ',' << dataStruct.key2 << ',' << dataStruct.str << '\n';
  return s;
}

bool operator<(const DataStruct &lhs, const DataStruct &rhs) {
  if (lhs.key1 == rhs.key1){
    if (lhs.key2 == rhs.key2){
      return lhs.str.length() < rhs.str.length();
    }
    return lhs.key2 < rhs.key2;
  }
  return lhs.key1 < rhs.key1;
}

