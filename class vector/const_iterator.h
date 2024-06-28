#ifndef CONST_ITERATOR
#define CONST_ITERATOR

#include <iterator>
#include <cstddef>
#include <cstdint>

template<typename T>
class ConstIterator {
 public:
  using iterator_category = std::random_access_iterator_tag; // NOLINT
  using difference_type = std::ptrdiff_t; // NOLINT
  using value_type = T; // NOLINT
  using pointer = const T*; // NOLINT
  using reference = const T&; // NOLINT

  explicit ConstIterator(pointer ptr) : ptr_(ptr) {}
  const T& operator*() const {
    return *ptr_;
  }
  const T* operator->() {
    return ptr_;
  }
  ConstIterator& operator++() {
    ++ptr_;
    return *this;
  }
  const ConstIterator operator++(int) {
    const ConstIterator helper = *this;
    ++(*this);
    return helper;
  }
  ConstIterator& operator--() {
    --ptr_;
    return *this;
  }
  const ConstIterator operator--(int) {
    const ConstIterator helper = *this;
    --(*this);
    return helper;
  }
  friend bool operator==(const ConstIterator& first, const ConstIterator& second) {
    return first.ptr_ == second.ptr_;
  }
  friend bool operator!=(const ConstIterator& first, const ConstIterator& second) {
    return first.ptr_ != second.ptr_;
  }
  friend bool operator>(const ConstIterator& first, const ConstIterator& second) {
    return first.ptr_ > second.ptr_;
  }
  friend bool operator<(const ConstIterator& first, const ConstIterator& second) {
    return first.ptr_ < second.ptr_;
  }
  friend bool operator>=(const ConstIterator& first, const ConstIterator& second) {
    return first.ptr_ >= second.ptr_;
  }
  friend bool operator<=(const ConstIterator& first, const ConstIterator& second) {
    return first.ptr_ <= second.ptr_;
  }
  friend difference_type operator-(const ConstIterator& first, const ConstIterator& second) {
    return (first.ptr_ - second.ptr_);
  }
  friend ConstIterator operator+(const ConstIterator& iterator, const int64_t& value) {
    Iterator result = iterator;
    result.ptr_ += value;
    return result;
  }
  friend ConstIterator operator-(const ConstIterator& iterator, const int64_t& value) {
    Iterator result = iterator;
    result.ptr_ -= value;
    return result;
  }
  ConstIterator &operator+=(const int64_t& value) {
    ptr_ += value;
    return *this;
  }
  ConstIterator &operator-=(const int64_t& value) {
    ptr_ -= value;
    return *this;
  }

 private:
  pointer ptr_;
};

#endif