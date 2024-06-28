#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H
#include <algorithm>
#include <list>
#include <vector>

template <class KeyT>
class UnorderedSet {
 public:
  UnorderedSet() = default;
  explicit UnorderedSet(size_t count);

  template <class ForwardIterator>
  UnorderedSet(ForwardIterator begin, ForwardIterator end);

  UnorderedSet(const UnorderedSet&);
  UnorderedSet(UnorderedSet&&) noexcept;

  UnorderedSet& operator=(const UnorderedSet&);
  UnorderedSet& operator=(UnorderedSet&&) noexcept;

  size_t Size() const;
  bool Empty() const;
  void Clear();

  bool Insert(const KeyT&);
  bool Insert(KeyT&&);
  void Erase(const KeyT&);
  bool Find(const KeyT&) const;

  void Rehash(size_t new_bucket_count);
  void Reserve(size_t new_bucket_count);

  size_t BucketCount() const;
  size_t BucketSize(size_t id) const;
  size_t Bucket(KeyT key) const;
  double LoadFactor() const;

 private:
  std::vector<std::list<KeyT>> keys_ = {};
  size_t count_elements_ = 0;
};

// Конструкторы
template <class KeyT>
UnorderedSet<KeyT>::UnorderedSet(size_t count) : keys_(count) {
}

template <class KeyT>
template <class ForwardIterator>
UnorderedSet<KeyT>::UnorderedSet(ForwardIterator begin, ForwardIterator end) : keys_(std::distance(begin, end)) {
  count_elements_ = std::distance(begin, end);
  for (; begin != end; ++begin) {
    size_t bucket_index = std::hash<KeyT>{}(*begin) % count_elements_;
    keys_[bucket_index].push_back(*begin);
  }
}

template <class KeyT>
UnorderedSet<KeyT>::UnorderedSet(const UnorderedSet& other)
    : keys_(other.keys_), count_elements_(other.count_elements_) {
}

template <class KeyT>
UnorderedSet<KeyT>::UnorderedSet(UnorderedSet&& other) noexcept
    : keys_(other.keys_), count_elements_(other.count_elements_) {
  other.keys_ = {};
  other.count_elements_ = 0;
}

// Присваивание
template <class KeyT>
UnorderedSet<KeyT>& UnorderedSet<KeyT>::operator=(const UnorderedSet& other) {
  keys_ = other.keys_;
  count_elements_ = other.count_elements_;
  return *this;
}

template <class KeyT>
UnorderedSet<KeyT>& UnorderedSet<KeyT>::operator=(UnorderedSet&& other) noexcept {
  keys_ = other.keys_;
  count_elements_ = other.count_elements_;
  other.Clear();
  return *this;
}

// Методы
template <class KeyT>
size_t UnorderedSet<KeyT>::Size() const {
  return count_elements_;
}

template <class KeyT>
bool UnorderedSet<KeyT>::Empty() const {
  return count_elements_ == 0;
}

template <class KeyT>
void UnorderedSet<KeyT>::Clear() {
  count_elements_ = 0;
  keys_ = {};
}

template <class KeyT>
void UnorderedSet<KeyT>::Erase(const KeyT& key) {
  size_t bucket_index = Bucket(key);
  if (keys_[bucket_index].empty()) {
    return;
  }
  auto it = std::find(keys_[bucket_index].begin(), keys_[bucket_index].end(), key);
  keys_[bucket_index].erase(it);
  count_elements_ -= 1;
}

template <class KeyT>
bool UnorderedSet<KeyT>::Find(const KeyT& key) const {
  if (keys_.empty()) {
    return false;
  }
  size_t bucket_index = Bucket(key);
  if (keys_[bucket_index].empty()) {
    return false;
  }
  auto it = std::find(keys_[bucket_index].begin(), keys_[bucket_index].end(), key);
  return it != keys_[bucket_index].end();
}

template <class KeyT>
void UnorderedSet<KeyT>::Rehash(size_t new_bucket_count) {
  if (new_bucket_count != keys_.size() && new_bucket_count >= count_elements_) {
    std::vector<std::list<KeyT>> new_table(new_bucket_count);
    for (size_t i = 0; i < keys_.size(); i++) {
      for (auto& el : keys_[i]) {
        size_t bucket_index = std::hash<KeyT>{}(el) % new_bucket_count;
        new_table[bucket_index].push_back(std::move(el));
      }
    }
    keys_ = std::move(new_table);
  }
}

template <class KeyT>
void UnorderedSet<KeyT>::Reserve(size_t new_bucket_count) {
  if (new_bucket_count > keys_.size()) {
    this->Rehash(new_bucket_count);
  }
}

template <class KeyT>
bool UnorderedSet<KeyT>::Insert(const KeyT& key) {
  if (this->BucketCount() == 0) {
    keys_.resize(1);
  }
  if (Find(key)) {
    return false;
  }
  if (this->LoadFactor() >= 1) {
    this->Rehash(BucketCount() * 2);
  }
  size_t bucket_index = Bucket(key);
  keys_[bucket_index].push_back(std::move(key));
  count_elements_ += 1;
  return true;
}

template <class KeyT>
bool UnorderedSet<KeyT>::Insert(KeyT&& key) {
  if (this->BucketCount() == 0) {
    keys_.resize(1);
  }
  if (Find(key)) {
    return false;
  }
  if (this->LoadFactor() >= 1) {
    this->Rehash(BucketCount() * 2);
  }
  size_t bucket_index = Bucket(key);
  keys_[bucket_index].push_back(std::move(key));
  count_elements_ += 1;
  return true;
}

template <class KeyT>
size_t UnorderedSet<KeyT>::BucketCount() const {
  return keys_.size();
}

template <class KeyT>
size_t UnorderedSet<KeyT>::BucketSize(size_t id) const {
  if (count_elements_ == 0 || id > keys_.size() - 1) {
    return 0;
  }
  return keys_[id].size();
}

template <class KeyT>
size_t UnorderedSet<KeyT>::Bucket(KeyT key) const {
  if (keys_.empty()) {
    return 0;
  }
  return std::hash<KeyT>{}(key) % keys_.size();
}

template <class KeyT>
double UnorderedSet<KeyT>::LoadFactor() const {
  if (count_elements_ == 0) {
    return 0;
  }
  return 1.0 * count_elements_ / keys_.size();
}
#endif  // UNORDERED_SET_H
