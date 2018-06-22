#ifndef B3_QUEWITHPRIORITY_HPP
#define B3_QUEWITHPRIORITY_HPP

#include <string>
#include <list>
#include <iostream>

template <typename QueueElement>
class QueueWithPriority {
  public:
  enum ElementPriority {
    LOW,
    NORMAL,
    HIGH
  };

  void putToQueue(const QueueElement &element, ElementPriority priority);
  void popFromQueue();
  void accelerate();
  bool printNextEl() const;
  int  definePriority() const;
  QueueElement getNextElement() const;

  private:
  std::list<QueueElement> queue_[3];
};

template <typename QueueElement>
void QueueWithPriority<QueueElement>::putToQueue(const QueueElement &element, ElementPriority priority) {
  queue_[priority].push_back(element);
}

template <typename QueueElement>
void QueueWithPriority<QueueElement>::popFromQueue() {
  int priority = definePriority();
  if (priority < 0) {
    throw std::out_of_range("Queue empty!");
  }
  queue_[priority].pop_front();
}

template <typename T>
int QueueWithPriority<T>::definePriority() const {
  int priority = HIGH;
  while ((priority >= 0) && (queue_[priority].empty())) {
    --priority;
  }
  return priority;
}

template <typename T>
void QueueWithPriority<T>::accelerate() {
  queue_[HIGH].splice(queue_[HIGH].end(), queue_[LOW]);
}

template <typename T>
bool QueueWithPriority<T>::printNextEl() const {
  int priority = definePriority();
  if (priority < 0) {
    std::cout << "<EMPTY>\n";
    return false;
  } else {
    std::cout << queue_[priority].front() << "\n";
    return true;
  }
}

template <typename QueueElement>
QueueElement QueueWithPriority<QueueElement>::getNextElement() const {
  int priority = definePriority();
  if (priority < 0) {
    throw std::out_of_range("Queue is empty!");
  }
  return queue_[priority].front();
}

#endif

