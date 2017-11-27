
#pragma once
#include "list.hpp"

#include <iostream>

template <typename T>
class LLNode {
public:
  LLNode(T value) {
    this->_value = value;
    this->_next = nullptr;
  }

  ~LLNode() {

  }

  LLNode<T>* next() {
    return this->_next;
  }

  void setNext(LLNode<T>* newNext) {
    this->_next = newNext;
  }

  T value() {
    return this->_value;
  }

private:
  T _value;
  LLNode<T>* _next;
};

template <typename T>
class LinkedList : public List<T> {
public:
  LinkedList() {
    this->_size = 0;
    this->_head = nullptr;
  }

  ~LinkedList() {
    this->clear();
  }

  void pop_front() {
    LLNode<T>* tmp = this->_head;
    this->_head = this->_head->next();
    delete tmp;
    this->_size -= 1;
  }

  void push_front(const T value) {
    LLNode<T>* newNode = new LLNode<T>(value);
    LLNode<T>* tmp = this->_head;
    newNode->setNext(this->_head);
    this->_head = newNode;
    this->_size += 1;
  }

  T get(int index) {
    if (index >= this->_size) {
      throw new std::logic_error("Out of bounds");
    }

    LLNode<T>* tmp = this->_head;
    while (index-- > 0) {
      tmp = tmp->next();
    }

    return tmp->value();
  }

  void pop_back() {
    if (this->_size == 0) {
      return;
    }

    if (this->_size == 1) {
      delete this->_head;
      this->_head = nullptr;    // is this necessary?
      this->_size -= 1;
      return;
    }

    if (this->_size == 2) {
      delete this->_head->next();
      this->_head->setNext(nullptr);    // is this necessary?
      this->_size -= 1;
      return;
    }

    LLNode<T>* tmp = this->_head;
    while (tmp->next()->next() != nullptr) {
      tmp = tmp->next();
    }

    // std::cout << tmp->value() << std::endl;
    delete tmp->next();
    tmp->setNext(nullptr);
    this->_size -= 1;
  }

  void push_back(const T value) {
    if (this->_head == nullptr) {
      this->_head = new LLNode<T>(value);
    } else {
      LLNode<T>* newNode = new LLNode<T>(value);
      this->getLastNode()->setNext(newNode);
    }
    this->_size += 1;
  }

  std::size_t size() const {
    return this->_size;
  }

  T front() {
    return this->_head->value();
  }

  T back() {
    return this->getLastNode()->value();
  }

  int countNodes() {
    if (this->_head == nullptr) {
      return 0;
    }

    int count = 1;
    LLNode<T>* tmp = this->_head;
    while (tmp->next() != nullptr) {
      tmp = tmp->next();
      count += 1;
    }

    return count;
  }

  bool empty() const {
    return this->_size == 0;
  }

  void clear() noexcept {
    delete this->_head;
    // TODO: delete rest of nodes as well. this currently leaks memory
    //throw new std::logic_error("Not yet implemented.");
  }

  T* toArray() {
    T* arr = new T[this->_size];
    for (int i = 0; i < this->_size; i++) {
      // TODO: this is slow, re-iterates the list every time
      // will be better with iterator implemented
      arr[i] = this->get(i);
    }

    return arr;
  }
private:
  int _size;
  LLNode<T>* _head;

  LLNode<T>* getLastNode() {
    LLNode<T>* tmp = this->_head;
    while(tmp->next() != nullptr) {
      tmp = tmp->next();
    }

    return tmp;
  }
};