#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#include <future>

template <typename T>
class SharedPtr {
public:
  SharedPtr();
  explicit SharedPtr(T*);
  SharedPtr(const SharedPtr&);
  SharedPtr(SharedPtr&&) noexcept;

  SharedPtr& operator=(const SharedPtr&);
  SharedPtr& operator=(SharedPtr&&) noexcept;

  void Reset(T* ptr = nullptr);
  void Swap(SharedPtr&);
  T* Get() const;
  size_t UseCount() const;

  T* operator->() const;
  T& operator*() const;

  explicit operator bool() const;

  ~SharedPtr();
private:
  T* ptr_ = nullptr;
  size_t* strong_counter_ = nullptr;
};

// Деструктор.
template <typename T> SharedPtr<T>::~SharedPtr(){
  if (strong_counter_ == nullptr) {
    return;
  }
  if (*strong_counter_ > 1) {
    --*strong_counter_;
    return;
  }
  delete ptr_;
  delete strong_counter_;
}

// Конструкторы.
template <typename T>  SharedPtr<T>::SharedPtr() : ptr_(nullptr) {
}

template <typename T>  SharedPtr<T>::SharedPtr(T* ptr) : ptr_(ptr) {
  if (ptr != nullptr) {
    strong_counter_ = new size_t(1);
  }
}

template <typename T>  SharedPtr<T>::SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), strong_counter_(other.strong_counter_) {
  if (strong_counter_ != nullptr) {
    ++*strong_counter_;
  }
}

template <typename T>  SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), strong_counter_(other.strong_counter_) {
  other.ptr_ = nullptr;
  other.strong_counter_ = nullptr;
}

// Присваивание.
template <typename T> SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other) noexcept {
  if (this != &other) {
    this->~SharedPtr();
    ptr_ = other.ptr_;
    strong_counter_ = other.strong_counter_;
    other.ptr_ = nullptr;
    other.strong_counter_ = nullptr;
  }
  return *this;
}

template <typename T> SharedPtr<T> & SharedPtr<T>::operator=(const SharedPtr& other){
  if (this != &other) {
    this->~SharedPtr();
    ptr_ = other.ptr_;
    strong_counter_ = other.strong_counter_;
    if (strong_counter_ != nullptr) {
      ++*strong_counter_;
    }
  }
  return *this;
}


// Методы.
template <typename T> T * SharedPtr<T>::Get() const{
  return ptr_;
}

template <typename T> void SharedPtr<T>::Reset(T *ptr) {
  this->~SharedPtr();
  if (ptr == nullptr) {
    strong_counter_ = nullptr;
  } else {
    strong_counter_ = new size_t(1);
  }
  ptr_ = ptr;
}

template <typename T> size_t SharedPtr<T>::UseCount() const{
  return strong_counter_ == nullptr ? 0 : *strong_counter_;
}

template <typename T> void SharedPtr<T>::Swap(SharedPtr& other){
  std::swap(ptr_, other.ptr_);
  std::swap(strong_counter_, other.strong_counter_);
}

// Операторы.
template <typename T> T& SharedPtr<T>::operator*() const{
  return *ptr_;
}

template <typename T> T* SharedPtr<T>::operator->() const{
  return ptr_;
}

template <typename T> SharedPtr<T>::operator bool() const{
  return ptr_ != nullptr;
}
#endif //SHARED_PTR_H
