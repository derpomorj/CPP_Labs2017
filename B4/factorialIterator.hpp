#ifndef B4_FACTORIALITERATOR_HPP
#define B4_FACTORIALITERATOR_HPP


#include <iterator>

class factorialIterator: public std::iterator<std::bidirectional_iterator_tag,long long> {
  public:
  factorialIterator();
  explicit factorialIterator(int);
  bool operator ==(const factorialIterator & rhs) const;
  bool operator !=(const factorialIterator & rhs) const;
  long long& operator *();
  long long* operator ->();
  factorialIterator& operator ++();
  factorialIterator operator ++(int);
  factorialIterator& operator --();
  factorialIterator operator --(int);
  private:
  long long value_;
  int base_;
};

#endif

