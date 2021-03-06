
#pragma once

#include <sstream>

#include "list.hpp"

template <typename T>
class UllNode {
public:
  UllNode(int size) {
    this->totalCapacity = size;
    this->arr = new T[size];
    this->numElements = 0;
    this->_next = nullptr;
  }

  ~UllNode() {
    // delete this->_next;
    delete[] this->arr;
  }

  T get(int index) {
    return this->arr[index];
  }

  /**
   * Places an item at the last available spot in the node's array
   */
  void push_back(T item) {
    this->arr[this->numElements] = item;
    this->numElements += 1;
  }

  void clearUpperRange() {
    this->numElements /= 2;
  }

  void setNext(UllNode<T>* newNext) {
    this->_next = newNext;
  }

  UllNode<T>* next() {
    return this->_next;
  }

  bool isFull() {
    return this->totalCapacity == this->numElements;
  }

  int size() {
    return this->numElements;
  }

  T getLast() {
    return this->arr[this->numElements-1];
  }

  /*
   * Removes the first element in the list container, effectively reducing the
   * container size by one.
   */
  void pop_front() {
    for (int i = 0; i < this->numElements - 1; i++) {
      this->arr[i] = this->arr[i+1];
    }
    this->numElements -= 1;
  }

  /*
   * Removes the last element in the list container, effectively reducing the
   * container size by one.
   */
  void pop_back() {
    // don't need to modify the array - it's just "garbage memory" now
    this->numElements -= 1;
  }

  void push_front(const T val) {
    if (this->isFull()) {
      // yikes. TODO wat do
      return;
    }

    for (int i = this->numElements; i >= 0; i--) {
      this->arr[i+1] = this->arr[i];
    }

    this->arr[0] = val;
    this->numElements += 1;
  }

private:
  UllNode<T>* _next;
  int numElements;
  int totalCapacity;
  T* arr;
};

template <typename T>
class UnrolledLinkedList : public List<T> {
public:
  
  /**
   * Default constructor
   */
  UnrolledLinkedList() {
    this->_len = 0;
    this->_head = nullptr;
    this->_maxNumElementsPerNode = 16;
  }
  
  UnrolledLinkedList(int nodeSize) {
    this->_len = 0;
    this->_head = nullptr;
    this->_maxNumElementsPerNode = nodeSize;
  }

  ~UnrolledLinkedList() {
    delete _head;
    // this->clear(); causes a segfault
  }

  T get(int index) {
    UllNode<T>* tmp = this->_head;
    while (index >= this->_maxNumElementsPerNode) {
      index -= tmp->size();
      tmp = tmp->next();
    }

    return tmp->get(index);
  }

  void pop_front() {
    this->_head->pop_front();

    // TODO: check if need to rebalance the node
  }

  void push_front(const T item) {
    // invariant: node's should never be completely full, so we should
    // have room to insert
    this->_head->push_front(item);

    // TODO: check if need to rebalance the node
  }

  void pop_back() {
    this->getLastNode()->pop_back();

    // TODO: check if need to rebalance the node 
  }

  /**
   * Adds an item to the end of the list
   */
  void push_back(const T item) {
    if (this->_head == nullptr) {
      this->_head = new UllNode<T>(this->_maxNumElementsPerNode);
      this->_head->push_back(item);
      this->_len += 1;
    } else {
      UllNode<T>* tmp = this->getLastNode();

      if (!tmp->isFull()) {
        tmp->push_back(item);
        this->_len += 1;
      } else {
        // TODO move half of elements from `tmp` to `newNode`
        UllNode<T>* newNode = new UllNode<T>(this->_maxNumElementsPerNode);
        for (int i = tmp->size() / 2; i < tmp->size(); i++) {
          newNode->push_back(tmp->get(i));
        }
        newNode->push_back(item);
        tmp->clearUpperRange();
        tmp->setNext(newNode);
        this->_len += 1;
      }
    }
  }

  // TODO should actually return reference type.... we'll do that later....
  T front() {
    if (this->_len == 0) {
      throw new std::out_of_range("Empty list");
    }
    return this->_head->get(0);
  }

  // TODO should actually return reference type.... we'll do that later....
  T back() {
    if (this->_len == 0) {
      throw new std::out_of_range("Empty list");
    }
    return this->getLastNode()->getLast();
  }

  bool empty() const {
    return this->_head == nullptr || this->_head->size() == 0;
  }

  void clear() noexcept {
    UllNode<T>* tmp = this->_head;
    while (tmp->next() != nullptr) {
      UllNode<T>* tmp2 = tmp->next();
      delete tmp;
      tmp = tmp2;
    }

    delete tmp;
  }

  std::size_t size() const { return this->_len; }

  int numberOfLinks() const {
    int counter = 1;
    UllNode<T>* tmp = this->_head;
    while (tmp->next() != nullptr) {
      tmp = tmp->next();
      counter += 1;
    }

    return counter;
  }

  /**
   * Produces a string-representation which is useful for debugging and
   * development to get a holistic view of the data structure
   */
  std::string str() const {
    std::stringstream ss;
    ss << "{";

    UllNode<T>* tmp = this->_head;
    while (tmp != nullptr) {
      if (tmp != this->_head) {
        ss << ", ";
      }
      ss << "[";
      for (int i = 0; i < tmp->size(); i++) {
        if (i != 0) {
          ss << ", ";
        }
        ss << tmp->get(i);
      }
      ss << "]";

      tmp = tmp->next();
    }

    ss << "}";

    return ss.str();
  }

private:
  // The number of nodes in the data structure
  int _len;

  // number of items each node may have
  int _maxNumElementsPerNode;

  UllNode<T>* _head;

  UllNode<T>* getLastNode() {
    UllNode<T>* tmp = this->_head;
    while (tmp->next() != nullptr) {
      tmp = tmp->next();
    }

    return tmp;
  }
};


