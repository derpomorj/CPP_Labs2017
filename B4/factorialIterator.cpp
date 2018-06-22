#include "factorialIterator.hpp"

factorialIterator::factorialIterator():
  value_(1),
  base_(1)
{}

factorialIterator::factorialIterator(int value):
value_(1),
base_(value)
{
  for (int i = 2; i <= value ; ++i) {
    value_ *=i;
  }
}

bool factorialIterator::operator==(const factorialIterator &rhs) const {
  return value_ == rhs.value_;
}

bool factorialIterator::operator!=(const factorialIterator &rhs) const {
  return value_ != rhs.value_;
}

long long& factorialIterator::operator*() {
  return value_;
}

long long *factorialIterator::operator->()  {
  return &value_;
}

factorialIterator& factorialIterator::operator++() {
  ++base_;
  value_ *= base_;
  return *this;
}

factorialIterator factorialIterator::operator++(int) {
  factorialIterator temp = *this;
  ++(*this);
  return temp;
}

factorialIterator& factorialIterator::operator--() {
  if (base_ != 1) {
    value_ /= base_;
    --base_;
  }
  return *this;
}

factorialIterator factorialIterator::operator--(int) {
  factorialIterator temp = *this;
  --(*this);
  return temp;
}


