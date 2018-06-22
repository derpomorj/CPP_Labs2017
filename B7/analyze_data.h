#ifndef B7_ANALYZEDATA_H
#define B7_ANALYZEDATA_H

class AnalyzeData {
public:
  void operator ()(long long value);
  void print();

private:
  long long max_;
  long long min_;
  long long positive_;
  long long negative_;
  long long first_;
  long long last_;
  long long numElements_;
  long long oddSum_;
  long long evenSum_;
};

#endif

