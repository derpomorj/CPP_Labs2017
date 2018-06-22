#ifndef B5_IMPL_H
#define B5_IMPL_H

#include <iostream>
#include <vector>

struct DataStruct {
  int key1;
  int key2;
  std::string str;
};

void readDataStruct(std::vector<DataStruct>& vector);
int readKey(std::istringstream&);

std::ostream& operator << (std::ostream &s, const DataStruct& dataStruct);

bool operator<(const DataStruct &lhs, const DataStruct &rhs);

#endif

