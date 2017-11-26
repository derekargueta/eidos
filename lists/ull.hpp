
#pragma once
#include "list.hpp"

template <typename T>
class UllNode {
public:
  UllNode(int size) {
    this->arr = new T[size];
    this->numElements = 0;
    this->next = nullptr;
  }

  ~UllNode() {
    delete this->next;
    delete[] this->arr;
  }

  T get(int index) {
    return this->arr[index];
  }

  void push_back(T item) {
    this->arr[this->numElements] = item;
    this->numElements += 1;
  }

private:
  UllNode<T>* next;
  int numElements;
  T* arr;
};

template <typename T>
class UnrolledLinkedList : public List<T> {
public:
  UnrolledLinkedList() {
    this->_len = 0;
    this->_head = nullptr;
  }
  UnrolledLinkedList(int nodeSize) {
    this->_len = 0;
    this->_head = nullptr;
  }
  ~UnrolledLinkedList() {
    // TODO: delete all connected nodes, not just head
    delete _head;
  }

  T get(int index) {
    UllNode<T>* tmp = this->_head;
    while (index > this->_maxNumElementsPerNode) {
      index -= this->_maxNumElementsPerNode;
    }

    return tmp->get(index);
  }
  void push_back(T item) {
    if (this->_head == nullptr) {
      this->_head = new UllNode<T>(this->_maxNumElementsPerNode);
      this->_head->push_back(item);
      this->_len += 1;
    } else {
      UllNode<T>* tmp = this->_head;
    }
  }
  int size() { return this->_len; }
private:
  int _len;
  int _maxNumElementsPerNode;
  UllNode<T>* _head;
};


