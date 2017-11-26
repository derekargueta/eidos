
#pragma once

template <typename T>
class List {
public:
  List() {}
  virtual ~List() {}
  virtual void pop_front() = 0;
  virtual void push_front(const T) = 0;
  virtual void pop_back() = 0;
  virtual void push_back(const T) = 0;
  virtual std::size_t size() const = 0;
  virtual T front() = 0;
  virtual T back() = 0;
  virtual bool empty() const = 0;
  virtual void clear() noexcept = 0;
};

