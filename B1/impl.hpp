#ifndef IMPL_HPP
#define IMPL_HPP

#include <iostream>
#include <functional>
#include <cstring>
#include "tasks.hpp"

namespace  detail {

  template<typename Container>
  struct AccessByBrackets {
    static typename Container::reference getElement(Container& vector, std::size_t index) {
      return vector[index];
    }
    static std::size_t begin(const Container &) {
      return 0;
    }
    static std::size_t end(const Container &cont) {
      return cont.size();
    }
  };

  template<typename Container>
  struct  AccessByAt {
    static typename Container::reference getElement(Container &container, size_t i) {
      return container.at(i);
    }
    static size_t begin(const Container &) {
      return 0;
    }
    static size_t end(const Container &cont) {
      return cont.size();
    }
  };

  template<typename Container>
  struct AccessByIterator {
    static typename Container::reference getElement(Container &, typename Container::iterator iterator) {
      return *iterator;
    }
    static typename Container::iterator begin(Container &cont) {
      return cont.begin();
    }
    static typename Container::iterator end(Container &cont) {
      return cont.end();
    }
  };

  template<typename T>
  std::function<bool(T,T)> setSortDirection(const char* sortType)
  {
    if (strcmp(sortType, "ascending") == 0) {
      return std::function<bool(T, T)>(std::less<T>());
    }
    if (strcmp(sortType, "descending") == 0) {
      return std::function<bool(T, T)>(std::greater<T>());
    }
    throw std::invalid_argument("invalid type of sort");
  }

  template<template <typename> class getAccess, class Container, typename Comparator>
  void sort(Container& container, Comparator compare)
  {
    auto begin = getAccess<Container>::begin(container);
    auto end = getAccess<Container>::end(container);
    if (begin == end) {
      return;
    }
    for (auto it1 = begin; it1 != end; ++it1) {
      for (auto it2 = begin; it2 != end; ++it2) {
        if (compare(getAccess<Container>::getElement(container, it1),
                    getAccess<Container>::getElement(container, it2))) {
          std::swap(getAccess<Container>::getElement(container, it1),
                    getAccess<Container>::getElement(container, it2));
        }
      }
    }
  }

  template <typename T>
  void readWithPushBack(T& container)
  {
    typename T::value_type i = 0;
    while (std::cin && !(std::cin >> i).eof()) {
      if (std::cin.fail() || std::cin.bad()) {
        throw std::ios_base::failure("reading failure");
      }
      container.push_back(i);
    }
  }

  template<typename T>
  void printCollection(const T& container, const bool printNewLine = true, const bool gap = true)
  {
    if (container.empty()){
      return;
    }

    if (gap) {
      for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
      }
    } else {
      for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it;
      }
    }
    if (printNewLine) {
      std::cout << "\n";
    }
  }

  void fillRandom(double * array, int size);
}

#endif

