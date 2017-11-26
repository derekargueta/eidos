
#pragma once
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

  // TODO this actually requires moving things in the array
  void clearLowerRange() {
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
    // TODO: delete all connected nodes, not just head
    delete _head;
  }

  T get(int index) {
    UllNode<T>* tmp = this->_head;
    while (index >= this->_maxNumElementsPerNode) {
      index -= tmp->size();
      tmp = tmp->next();
    }

    return tmp->get(index);
  }

  /**
   * Adds an item to the end of the list
   */
  void push_back(T item) {
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

  int size() { return this->_len; }

  int numberOfLinks() {
    int counter = 1;
    UllNode<T>* tmp = this->_head;
    while (tmp->next() != nullptr) {
      tmp = tmp->next();
      counter += 1;
    }

    return counter;
  }
private:
  int _len;
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


