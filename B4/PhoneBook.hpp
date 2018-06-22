#ifndef B4_PHONEBOOK_HPP
#define B4_PHONEBOOK_HPP

#include <list>
#include "user.hpp"

class PhoneBook {
  public:
  using IteratorType = std::list<user_t>::iterator;
  std::list<IteratorType>::iterator begin();
  std::list<IteratorType>::iterator end();
  void advance(std::list<IteratorType>::iterator&,int distance);
  void insert(const user_t& user, std::list<IteratorType>::iterator, bool insertBeforeIterator);
  void pushBack(const user_t& user);
  std::list<IteratorType>::iterator removeElement(std::list<IteratorType>::iterator&);
  void show(const std::list<IteratorType>::iterator&) const;
  bool empty() const;

  private:
  std::list<user_t> data_;
  std::list<IteratorType> dataIterators_;
};

#endif

