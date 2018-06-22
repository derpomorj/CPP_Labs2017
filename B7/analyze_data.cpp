#include "analyze_data.h"
#include <iostream>
#include <iomanip>

void AnalyzeData::operator()(long long value) {
  if (value > 0) {
    ++positive_;
  } else if (value < 0) {
    ++negative_;
  }
  if (value % 2 == 0) {
    evenSum_ += value;
  } else {
    oddSum_ += value;
  }
  if (numElements_ == 0) {
    first_ = value;
    max_ = value;
    min_ = max_;
  }
  max_ = std::max(max_, value);
  min_ = std::min(min_, value);
  last_ = value;
  ++numElements_;
}

void AnalyzeData::print() {
  if (numElements_ == 0) {
    std::cout << "No Data" << "\n";
    return;
  }
  auto mean = double((evenSum_ + oddSum_)) / numElements_;
  std::cout << "Max: " << max_ << "\n";
  std::cout << "Min: " << min_ << "\n";
  std::cout << "Mean: " << std::setprecision(1) << std::fixed << mean << "\n";
  std::cout << "Positive: " << positive_ << "\n";
  std::cout << "Negative: " << negative_ << "\n";
  std::cout << "Odd Sum: " << oddSum_ << "\n";
  std::cout << "Even Sum: " << evenSum_ << "\n";
  std::cout << "First/Last Equal: " << (first_ == last_ ? "yes" : "no") << "\n";
}

