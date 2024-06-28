#ifndef ITERATOR
#define ITERATOR

#include <iterator>
#include <cstddef>
#include <cstdint>

template<typename T>
class Iterator {
 public:
  using iterator_category = std::random_access_iterator_tag; // NOLINT
  using difference_type = std::ptrdiff_t; // NOLINT
  using value_type = T; // NOLINT
  using pointer = T*; // NOLINT
  using reference = T&; // NOLINT

  explicit Iterator(pointer ptr) : ptr_(ptr) {}
  reference operator*() const {
    return *ptr_;
  }
  pointer operator->() {
    return ptr_;
  }
  Iterator& operator++() {
    ++ptr_;
    return *this;
  }
  const Iterator operator++(int) {
    const Iterator helper = *this;
    ++(*this);
    return helper;
  }
  Iterator& operator--() {
    --ptr_;
    return *this;
  }
  const Iterator operator--(int) {
    const Iterator helper = *this;
    --(*this);
    return helper;
  }
  friend bool operator==(const Iterator& first, const Iterator& second) {
    return first.ptr_ == second.ptr_;
  }
  friend bool operator!=(const Iterator& first, const Iterator& second) {
    return first.ptr_ != second.ptr_;
  }
  friend bool operator>(const Iterator& first, const Iterator& second) {
    return first.ptr_ > second.ptr_;
  }
  friend bool operator<(const Iterator& first, const Iterator& second) {
    return first.ptr_ < second.ptr_;
  }
  friend bool operator>=(const Iterator& first, const Iterator& second) {
    return first.ptr_ >= second.ptr_;
  }
  friend bool operator<=(const Iterator& first, const Iterator& second) {
    return first.ptr_ <= second.ptr_;
  }
  friend difference_type operator-(const Iterator& first, const Iterator& second) {
    return (first.ptr_ - second.ptr_);
  }
  friend Iterator operator+(const Iterator& iterator, const int64_t& value) {
    Iterator result = iterator;
    result.ptr_ += value;
    return result;
  }
  friend Iterator operator-(const Iterator& iterator, const int64_t& value) {
    Iterator result = iterator;
    result.ptr_ -= value;
    return result;
  }
  Iterator& operator+=(const int64_t value) {
    ptr_ += value;
    return *this;
  }
  Iterator& operator-=(const int64_t value) {
    ptr_ -= value;
    return *this;
  }

 private:
  pointer ptr_;
};

#endif