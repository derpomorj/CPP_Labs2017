#include "PhoneBook.hpp"
#include <iostream>

void PhoneBook::advance(std::list<std::list<user_t>::iterator>::iterator& iterator,int distance) {
  if (distance == 0) {
    return;
  }

  if (distance > 0) {
    long currentDist = std::distance(iterator, dataIterators_.end());
    if (currentDist < distance) {
      throw std::out_of_range("invalid distance");
    }
  } else {
    long currentDist = std::distance(dataIterators_.begin(),iterator);
    if (currentDist < -distance) {
      throw std::out_of_range("invalid distance");
    }
  }
  std::advance(iterator, distance);
}

void PhoneBook::insert(const user_t& user,std::list<IteratorType>::iterator iterator, bool insertBeforeIterator) {
  if (insertBeforeIterator) {
    dataIterators_.insert(iterator, data_.insert(*iterator, user));
  } else {
    auto it = *iterator;
    dataIterators_.insert(++iterator, data_.insert(++it, user));
  }
}

void PhoneBook::pushBack(const user_t& user) {
  if (data_.empty()) {
    data_.push_back(user);
    dataIterators_.push_back(data_.begin());
  } else {
    data_.push_back(user);
    dataIterators_.push_back(--data_.end());
  }
}

std::list<std::list<user_t>::iterator>::iterator PhoneBook::removeElement(std::list<IteratorType>::iterator& iterator) {
  data_.erase(*iterator);
  auto it = dataIterators_.erase(iterator);
  if (it == dataIterators_.end()) {
    return --it;
  } else {
    return it;
  }
}

bool PhoneBook::empty() const {
  return data_.empty();
}

std::list<std::list<user_t>::iterator>::iterator PhoneBook::begin() {
  return dataIterators_.begin();
}

std::list<std::list<user_t>::iterator>::iterator PhoneBook::end() {
  return dataIterators_.end();
}

void PhoneBook::show(const std::list<std::_List_iterator<user_t>>::iterator& iterator) const {
  if (empty()) {
    std::cout << "<EMPTY>\n";
  } else {
    std::cout << (**iterator).number_ <<" "
              << (**iterator).name_ << "\n";
  }
}

