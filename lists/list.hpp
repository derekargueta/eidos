
#pragma once

template <typename T>
class List {
public:
  List() {}
  virtual ~List() {}
  virtual void push_back(T) = 0;
  virtual int size() = 0;
  virtual T front() = 0;
  virtual T back() = 0;
};

