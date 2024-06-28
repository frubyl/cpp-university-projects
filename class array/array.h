#ifndef ARRAY_H
#define ARRAY_H
#define ARRAY_TRAITS_IMPLEMENTED

#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <typename T, size_t N>
class Array {
public:
  T array[N];

  T& operator[](size_t idx);
  T& At (size_t idx);

  const T& operator[](size_t idx) const;
  const T& At (size_t idx) const;

  const T& Front() const;
  const T& Back() const;
  const T* Data() const;
  T& Front();
  T& Back();
  T* Data();
  size_t Size() const;
  bool Empty() const;
  void Fill(const T& value);
  void Swap(Array<T, N>& other);
};

template <typename T, size_t N> T & Array<T, N>::operator[](size_t idx){
  return array[idx];
}

template <typename T, size_t N> const T & Array<T, N>::operator[](size_t idx) const{
  return array[idx];
}

template <typename T, size_t N> T & Array<T, N>::At(size_t idx){
  if (idx > N - 1) {
    throw ArrayOutOfRange();
  }
  return array[idx];
}

template <typename T, size_t N> const T & Array<T, N>::At(size_t idx) const{
  if (idx > N - 1) {
    throw ArrayOutOfRange();
  }
  return array[idx];
}

template <typename T, size_t N> const T& Array<T, N>::Back() const{
  return array[N - 1];
}

template <typename T, size_t N> const T& Array<T, N>::Front() const{
  return array[0];
}

template <typename T, size_t N> const T* Array<T, N>::Data() const{
  return array;
}

template <typename T, size_t N> T& Array<T, N>::Back() {
  return array[N - 1];
}

template <typename T, size_t N> T& Array<T, N>::Front() {
  return array[0];
}

template <typename T, size_t N> T* Array<T, N>::Data() {
  return array;
}

template <typename T, size_t N> bool Array<T, N>::Empty() const{
  return N == 0;
}

template <typename T, size_t N> size_t Array<T, N>::Size() const{
  return N;
}

template <typename T, size_t N> void Array<T, N>::Fill(const T &value){
  for(size_t i = 0; i < N; i++) {
    array[i] = value;
  }
}

template <typename T, size_t N> void Array<T, N>::Swap(Array<T, N>& other){
  for (size_t i = 0; i < N; i++) {
    auto tmp = array[i];
    array[i] = other.array[i];
    other.array[i] = tmp;
  }
}

template<typename T, class = std::enable_if_t<!std::is_array_v<T>>>
size_t GetNumElements(const T&) {
  return 1;
}

template<typename T, size_t N>
size_t GetSize(T(&)[N]) {
  return N;
}

template<typename T, class = std::enable_if_t<!std::is_array_v<T>>>
size_t GetSize(const T&) {
  return 0;
}

template<typename T, size_t N>
size_t GetNumElements(T(&array)[N]) {
  return GetSize(array) * GetNumElements(array[0]);
}

template<typename T, class = std::enable_if_t<!std::is_array_v<T>>>
size_t GetRank(const T&) {
  return 0;
}

template<typename T, size_t N>
size_t GetRank(T(&array)[N]) {
  return 1 + GetRank(array[0]);
}

#endif //ARRAY_H
