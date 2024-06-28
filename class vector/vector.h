#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <iterator>

// Все классы в одном файле, так как при отрпавке архива возникала ошибка, что в файл не в UTF-8 кодировке
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

template <typename T>
class Vector {
public:
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = size_t;
  using Iterator = Iterator<T>;
  using ConstIterator = ConstIterator<T>;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  Vector();
  Vector(const Vector&);
  Vector(Vector&&) noexcept;

  explicit Vector(SizeType size);
  explicit Vector(SizeType size, T value);

  template <class Iterator, class =
  std::enable_if_t<std::is_base_of_v<std::forward_iterator_tag, typename
  std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator first, Iterator last) : capacity_(std::distance(first, last)), size_(std::distance(first, last)) {
    if (size_ <= 0) {
      arr_ = nullptr;
    } else {
      arr_ = new ValueType[size_];
      try {
        std::copy(first, last, arr_);
      } catch (...) {
        delete[] arr_;
        throw;
      }
    }
  }

  Vector(std::initializer_list<T> list);

  [[nodiscard]] SizeType Size() const;
  [[nodiscard]] SizeType Capacity() const;
  [[nodiscard]] bool Empty() const;

  Vector& operator=(const Vector&);
  Vector& operator=(Vector&&) noexcept;

  ConstReference operator[](SizeType ind) const;
  Reference operator[](SizeType ind);

  ConstReference At(SizeType ind) const;
  Reference At(SizeType ind);

  ConstReference Front() const;
  Reference Front();

  ConstReference Back() const;
  Reference Back();

  Pointer Data();
  ConstPointer Data() const;

  void Swap(Vector&);
  void Resize(SizeType new_size);
  void Resize(SizeType new_size, ValueType value);
  void Reserve(SizeType new_cap);
  void ShrinkToFit();
  void Clear();

  void PushBack(ConstReference);
  void PushBack(ValueType&&);
  void PopBack();

  ~Vector();

  bool operator<(const Vector& other) const;
  bool operator>(const Vector& other) const;
  bool operator>=(const Vector& other) const;
  bool operator<=(const Vector& other) const;
  bool operator==(const Vector& other) const;
  bool operator!=(const Vector& other) const;

  Iterator begin();  // NOLINT
  Iterator end(); // NOLINT

  ConstIterator begin() const; // NOLINT
  ConstIterator end() const; // NOLINT

  ConstIterator cbegin() const; // NOLINT
  ConstIterator cend() const; // NOLINT

  ReverseIterator rbegin(); // NOLINT
  ReverseIterator rend(); // NOLINT

  ConstReverseIterator rbegin() const; // NOLINT
  ConstReverseIterator rend() const; // NOLINT

  ConstReverseIterator crbegin() const; // NOLINT
  ConstReverseIterator crend() const; // NOLINT

private:
  SizeType capacity_;
  SizeType size_;
  Pointer arr_;
};

// Конструкторы
template <typename T>  Vector<T>::Vector() : capacity_(0), size_(0), arr_(nullptr){
}

template <typename T>  Vector<T>::Vector(const Vector& v) : capacity_(v.capacity_), size_(v.size_) {
  if (size_ <= 0) {
    arr_ = nullptr;
  } else {
    arr_ = new ValueType[size_];
    try {
      std::copy(v.arr_, v.arr_ + size_, arr_);
    } catch (...) {
      delete[] arr_;
      throw;
    }
  }
}

template <typename T>  Vector<T>::Vector(Vector && v) noexcept : capacity_(v.capacity_), size_(v.size_), arr_(v.arr_) {
  v.arr_ = nullptr;
  v.capacity_ = 0;
  v.size_ = 0;
}

template <typename T>  Vector<T>::Vector(SizeType size) : capacity_(size), size_(size), arr_(new ValueType[size]){
}

template <typename T>  Vector<T>::Vector(SizeType size, T value) : capacity_(size), size_(size) {
  if (size <= 0) {
    arr_ = nullptr;
    size_ = 0;
  } else {
    arr_ = new ValueType[size];
    try {
      for (SizeType i = 0; i < size; ++i) {
        arr_[i] = value;
      }
    } catch (...) {
      delete[] arr_;
      throw;
    }
  }
}

template <typename T>  Vector<T>::Vector(std::initializer_list<T> list) : capacity_(list.size()), size_(list.size()){
  if (size_ <= 0) {
    arr_ = nullptr;
  } else {
    arr_ = new ValueType[size_];
    try {
      std::copy(list.begin(), list.end(), arr_);
    } catch (...) {
      delete[] arr_;
      throw;
    }
  }
}

// Присваивание
template <typename T> Vector<T> & Vector<T>::operator=(const Vector & other){
  if (this != &other) {
    delete[] arr_;
    arr_ = nullptr;
    size_ = other.size_;
    capacity_ = other.capacity_;
    if (size_ != 0) {
      arr_ = new T[other.size_];
    }
    std::copy_n(other.Data(), size_, arr_);
  }
  return *this;
}

template <typename T> Vector<T> & Vector<T>::operator=(Vector &&other) noexcept{
  if (this != &other) {
    delete[] arr_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    arr_ = other.arr_;
    other.size_ = 0;
    other.capacity_ = 0;
    other.arr_ = nullptr;
  }
  return *this;
}

// Методы
template <typename T> typename Vector<T>::SizeType Vector<T>::Size() const{
  return size_;
}


template <typename T> typename Vector<T>::SizeType Vector<T>::Capacity() const{
  return capacity_;
}

template <typename T>  bool Vector<T>::Empty() const{
  return size_ == 0;
}

template <typename T>  typename Vector<T>::Reference Vector<T>::operator[](size_t ind){
  return arr_[ind];
}

template <typename T> typename Vector<T>::ConstReference Vector<T>::operator[](SizeType ind) const{
  return arr_[ind];
}

template <typename T> typename Vector<T>::Reference Vector<T>::At(SizeType ind){
  if (ind >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return arr_[ind];
}

template <typename T> typename Vector<T>::ConstReference  Vector<T>::At(SizeType ind) const{
  if (ind >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return arr_[ind];
}

template <typename T> typename Vector<T>::Reference Vector<T>::Front(){
  return arr_[0];
}

template <typename T> typename Vector<T>::ConstReference Vector<T>::Front() const{
  return arr_[0];
}

template <typename T> typename Vector<T>::ConstReference Vector<T>::Back() const {
  return arr_[size_ - 1];
}

template <typename T> typename Vector<T>::Reference Vector<T>::Back() {
  return arr_[size_ - 1];
}

template <typename T> typename Vector<T>::ConstPointer Vector<T>::Data() const{
  return arr_;
}

template <typename T> typename Vector<T>::Pointer Vector<T>::Data(){
  return arr_;
}

template <typename T> void Vector<T>::Swap(Vector &v){
  auto tmp_s = v.size_;
  auto tmp_c = v.capacity_;
  auto tmp_a = v.arr_;
  v.arr_ = arr_;
  v.capacity_ = capacity_;
  v.size_ = size_;
  arr_ = tmp_a;
  capacity_ = tmp_c;
  size_ = tmp_s;
}

template <typename T> void Vector<T>::Resize(SizeType new_size){
  if (new_size > capacity_) {
    auto new_arr = new ValueType[new_size];
    try {
      std::move(begin(), end(), new_arr);
      capacity_ = new_size;
      size_ = new_size;
      delete[] arr_;
      arr_ = std::move(new_arr);
    } catch (...) {
      delete[] new_arr;
      throw;
    }
  }
  if (new_size < capacity_) {
    size_ = new_size;
  }
}

template <typename T> void Vector<T>::Resize(SizeType new_size, ValueType value){
  if (new_size > capacity_) {
    auto new_arr = new ValueType[new_size];
    try {
      for (size_t i = 0; i < size_; ++i) {
        new_arr[i] = arr_[i];
      }
      for (size_t i = size_; i < new_size; ++i) {
        new_arr[i] = value;
      }
    } catch (...) {
      delete[] new_arr;
      throw;
    }
    T* tmp = arr_;
    capacity_ = new_size;
    arr_ = new_arr;
    delete[] tmp;
  }
  if (new_size < capacity_ && new_size > size_) {
    std::fill(begin() + size_, begin() + new_size, value);
  }
  size_ = new_size;
}

template <typename T> void Vector<T>::Reserve(SizeType new_cap){
  if (new_cap > capacity_) {
    auto new_arr = new ValueType[new_cap];
    try {
      std::move(begin(), end(), new_arr);
      delete[] arr_;
      arr_ = new_arr;
      capacity_ = new_cap;
    } catch (...) {
      delete[] new_arr;
      throw;
    }
  }
}

template <typename T> void Vector<T>::ShrinkToFit(){
  if (size_ == capacity_) {
    return;
  }
  if (size_ != 0) {
    auto new_arr = new ValueType[size_];
    try {
      std::move(begin(), end(), new_arr);
      delete[] arr_;
      arr_ = new_arr;
      capacity_ = size_;
    } catch (...) {
      delete[] new_arr;
      throw;
    }
  } else {
    capacity_ = 0;
    delete[] arr_;
    arr_ = nullptr;
  }
}

template <typename T> void Vector<T>::Clear(){
  size_ = 0;
  capacity_ = 0;
}

template <typename T> void Vector<T>::PushBack(ConstReference value){
  if (size_ < capacity_) {
    arr_[size_] = std::move(value);
    size_ += 1;
  } else {
    SizeType new_size = capacity_ > 0 ? capacity_ * 2 : 1;
    auto new_data = new T[new_size];
    try {
      for (size_t i = 0; i < size_; ++i) {
        new_data[i] = arr_[i];
      }
      new_data[size_] = std::move(value);
    } catch (...) {
      delete[] new_data;
      throw;
    }
    delete[] arr_;
    arr_ = new_data;
    ++size_;
    capacity_ = new_size;
  }
}
template <typename T> void Vector<T>::PushBack(ValueType && value){
  if (size_ >= capacity_) {
    auto new_capacity = capacity_ == 0 ? 1 : 2 * capacity_;
    auto new_arr = new T[new_capacity];
    std::move(begin(), end(), new_arr);
    delete[] arr_;
    arr_ = new_arr;
    capacity_ = new_capacity;
  }
  arr_[size_++] = std::move(value);
}

template <typename T> void Vector<T>::PopBack(){
  if (size_ > 0) {
    --size_;
  }
}

// Итераторы
template <typename T> typename Vector<T>::Iterator Vector<T>::begin() { // NOLINT
  return Vector::Iterator(arr_);
}

template <typename T> typename Vector<T>::Iterator Vector<T>::end() {  // NOLINT
  return Vector::Iterator(arr_ + size_);
}

template <typename T> typename Vector<T>::ConstIterator Vector<T>:: begin() const {  // NOLINT
  return Vector::ConstIterator(arr_);
}

template <typename T> typename Vector<T>::ConstIterator Vector<T>:: end() const {  // NOLINT
  return Vector::ConstIterator(arr_ + size_);
}
template <typename T> typename Vector<T>::ConstIterator Vector<T>:: cbegin() const {  // NOLINT
  return Vector::ConstIterator(arr_);
}
template <typename T> typename Vector<T>::ConstIterator Vector<T>:: cend() const {  // NOLINT
  return Vector::ConstIterator(arr_ + size_);
}
template <typename T> typename Vector<T>::ReverseIterator Vector<T>:: rbegin() {  // NOLINT
  return std::make_reverse_iterator(Iterator(arr_ + size_));
}
template <typename T> typename Vector<T>::ReverseIterator Vector<T>:: rend() {  // NOLINT
  return std::make_reverse_iterator(Iterator(arr_));
}
template <typename T> typename Vector<T>::ConstReverseIterator Vector<T>:: rbegin() const {  // NOLINT
  return std::make_reverse_iterator(ConstIterator(arr_ + size_));
}
template <typename T> typename Vector<T>::ConstReverseIterator Vector<T>:: rend() const {  // NOLINT
  return std::make_reverse_iterator(ConstIterator(arr_));
}
template <typename T> typename Vector<T>::ConstReverseIterator Vector<T>:: crbegin() const {  // NOLINT
  return std::make_reverse_iterator(ConstIterator(arr_ + size_));
}
template <typename T> typename Vector<T>::ConstReverseIterator Vector<T>:: crend() const {  // NOLINT
  return std::make_reverse_iterator(ConstIterator(arr_));
}

// Сравнения
template <typename T> bool Vector<T>::operator<(const Vector& other) const {
  return std::lexicographical_compare(arr_, arr_ + size_, other.Data(), other.Data() + other.Size());
}
template <typename T> bool Vector<T>::operator>(const Vector& other) const {
  return other < *this;
}
template <typename T> bool Vector<T>::operator>=(const Vector& other) const {
  return !(*this < other);
}
template <typename T> bool Vector<T>::operator<=(const Vector& other) const {
  return !(*this > other);
}
template <typename T> bool Vector<T>::operator==(const Vector& other) const {
  return size_ == other.Size() && std::equal(arr_, arr_ + size_, other.Data());
}
template <typename T> bool Vector<T>::operator!=(const Vector& other) const {
  return !(*this == other);
}

template <typename T>  Vector<T>::~Vector(){
  delete [] arr_;
}
#endif //VECTOR_H
