#pragma once
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <string>
// 21,39
template <typename T>
class MojVektor {
  public:
  class Iterator;
  MojVektor();
  MojVektor(const std::initializer_list<T>&);
  MojVektor(const MojVektor&);
  MojVektor& operator=(const MojVektor&);
  MojVektor(MojVektor&&);
  MojVektor& operator=(MojVektor&&);
  ~MojVektor();
  MojVektor& push_back(const T&);
  MojVektor& push_front(const T&);
  MojVektor& push_back(T&&);
  MojVektor& push_front(T&&);
  size_t size() const;
  T& at(size_t) const;
  T& operator[](size_t) const;
  void clear();
  void resize(size_t newSize, const T& difference_value);
  MojVektor& pop_back();
  MojVektor& pop_front();
  T& back() const;
  T& front() const;
  bool empty() const;
  size_t capacity() const;
  bool operator==(const MojVektor&) const;
  bool operator!=(const MojVektor&) const;
  bool full() const;
  MojVektor subvector(Iterator begin, Iterator end);
  Iterator begin() const;
  Iterator end() const;
  Iterator find(const T&) const;
  Iterator erase(Iterator pos);
  Iterator insert(Iterator, const T&);
  Iterator insert(Iterator, T&&);
  Iterator rbegin() const;
  Iterator rend() const;
  Iterator erase(Iterator beginIt, Iterator endIt);
  void rotate();
  void rotate(Iterator beginIt, Iterator endIt);

  T* data();

  private:
  void realoc();
  size_t capacity_;
  size_t size_;
  T* arr_;
};

// Implementacija ovdje
/*template <typename T>
std::ostringstream& operator <<(MojVektor<T> v, std::ostringstream& out){
  std::string s{", 0"};
  std::string brace1{"{"};
  std::string brace2{"}"};
  out<<brace1;
  for(auto i=v.begin();i!=v.end()-2;++i)
  {
    out<<*i<<s;
  }
  out<<v.back();
  return out;
} */

template <typename T>
void MojVektor<T>::realoc() {
  auto temp = new T[2 * capacity_];
  for (auto i = 0u; i < size_; ++i) temp[i] = std::move(arr_[i]);
  delete[] arr_;
  arr_ = temp;
  capacity_ *= 2;
  temp = nullptr;
}

template <typename T>
MojVektor<T>::MojVektor() : capacity_{10}, size_{0}, arr_{new T[capacity_]} {}

template <typename T>
MojVektor<T>::MojVektor(const std::initializer_list<T>& other)
    : capacity_{2 * other.size()}, size_{other.size()}, arr_{new T[capacity_]} {
  std::copy(other.begin(), other.end(), arr_);
}

template <typename T>
MojVektor<T>::MojVektor(const MojVektor& other)
    : capacity_{2 * other.size_}, size_{other.size_}, arr_{new T[capacity_]} {
  std::copy(other.arr_, other.arr_ + size_, arr_);
}

template <typename T>
MojVektor<T>& MojVektor<T>::operator=(const MojVektor& other) {
  delete[] arr_;
  arr_ = new T[other.capacity_];
  capacity_ = other.capacity_;
  size_ = other.size_;
  std::copy(other.arr_, other.arr_ + size_, arr_);
  return *this;
}

template <typename T>
MojVektor<T>::MojVektor(MojVektor&& other)
    : capacity_{other.capacity_}, size_{other.size_}, arr_{other.arr_} {
  other.arr_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <typename T>
MojVektor<T>& MojVektor<T>::operator=(MojVektor&& other) {
  delete[] arr_;
  capacity_ = other.capacity_;
  size_ = other.size_;
  arr_ = other.arr_;
  other.arr_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <typename T>
MojVektor<T>::~MojVektor() {
  delete[] arr_;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
MojVektor<T>& MojVektor<T>::push_back(const T& element) {
  if (capacity_ == size_) realoc();
  arr_[size_++] = element;
  return *this;
}

template <typename T>
MojVektor<T>& MojVektor<T>::push_front(const T& element) {
  if (capacity_ == size_) realoc();
  auto temp = *this;
  ++size_;
  arr_[0] = element;
  std::copy(temp.arr_, temp.arr_ + temp.size_, arr_ + 1);
  return *this;
}

template <typename T>
MojVektor<T>& MojVektor<T>::push_back(T&& element) {
  if (capacity_ == size_) realoc();
  arr_[size_++] = std::move(element);
  return *this;
}

template <typename T>
MojVektor<T>& MojVektor<T>::push_front(T&& element) {
  if (capacity_ == size_) realoc();
  auto temp = *this;
  arr_[0] = std::move(element);
  ++size_;
  std::copy(temp.arr_, temp.arr_ + temp.size_, arr_ + 1);
  return *this;
}

template <typename T>
size_t MojVektor<T>::size() const {
  return size_;
}

template <typename T>
T& MojVektor<T>::at(size_t index) const {
  if (index >= size_)
    throw std::out_of_range("indeks ne postoji");
  else
    return arr_[index];
}

template <typename T>
T& MojVektor<T>::operator[](size_t index) const {
  return arr_[index];
}

template <typename T>
void MojVektor<T>::clear() {
  delete[] arr_;
  size_ = 0;
  arr_ = nullptr;
  capacity_ = 0;
}

template <typename T>
void MojVektor<T>::resize(size_t newSize, const T& difference_value) {
  if (newSize > capacity_) {
    capacity_ = newSize;
    realoc();
  }
  if (newSize > size_) {
    for (auto i = size_; i < newSize; ++i) {
      arr_[i] = difference_value;
    }
  }

  size_ = newSize;
}

template <typename T>
MojVektor<T>& MojVektor<T>::pop_back() {
  if (size_ != 0) {
    back() = T{};
    --size_;
    return *this;
  } else
    throw std::out_of_range("");
}

template <typename T>
MojVektor<T>& MojVektor<T>::pop_front() {
  if (size_ != 0) {
    for (auto i = 0u; i < size_; ++i) {
      arr_[i] = arr_[i + 1];
    }
    --size_;
    return *this;
  } else
    throw std::out_of_range("");
}

template <typename T>
T& MojVektor<T>::back() const {
  if (size_ == 0)
    throw std::out_of_range("prazan kontejner");
  else
    return arr_[size_ - 1];
}

template <typename T>
T& MojVektor<T>::front() const {
  if (size_ == 0)
    throw std::out_of_range("prazan kontejner");
  else
    return arr_[0];
}

template <typename T>
bool MojVektor<T>::empty() const {
  return !size_;
}

template <typename T>
size_t MojVektor<T>::capacity() const {
  return capacity_;
}

template <typename T>
bool MojVektor<T>::operator==(const MojVektor& other) const {
  if (size_ != other.size_)
    return false;
  else {
    for (auto i = 0u; i < size_; ++i)
      if (arr_[i] != other[i]) return false;
    return true;
  }
}

template <typename T>
bool MojVektor<T>::operator!=(const MojVektor& other) const {
  return !(*this == other);
}

template <typename T>
bool MojVektor<T>::full() const {
  return size_ == capacity_;
}

template <typename T>
class MojVektor<T>::Iterator
    : public std::iterator<std::random_access_iterator_tag, T> {
  private:
  T* ptr_{arr_};

  public:
  Iterator() : ptr_{nullptr} {}
  Iterator(T* p) : ptr_{p} {}
  Iterator(const Iterator& it) : ptr_{it.ptr_} {}
  Iterator(Iterator&& it) : ptr_{it.ptr_} { it.ptr_ = nullptr; }
  Iterator& operator=(const Iterator& it) {
    ptr_ = it.ptr_;
    return *this;
  }
  Iterator& operator=(Iterator&& it) {
    ptr_ = it.ptr_;
    it.ptr_ = nullptr;
    return *this;
  }

  ~Iterator() { ptr_ = nullptr; }

  T& operator*() { return *ptr_; }

  operator bool () const{return ptr_;}

  Iterator& operator++() {
    ++ptr_;
    return *this;
  }
  Iterator operator++(int) {
    auto temp = ptr_;
    ++ptr_;
    return temp;
  }

  Iterator& operator--() {
    --ptr_;
    return *this;
  }
  Iterator operator--(int) {
    auto temp = ptr_;
    --ptr_;
    return temp;
  }

  bool operator!=(const Iterator& it) const { return ptr_ != it.ptr_; }
  bool operator==(const Iterator& it) const { return ptr_ == it.ptr_; }
  bool operator>=(const Iterator& it) const { return ptr_ >= it.ptr_; }
  bool operator<=(const Iterator& it) const { return ptr_ <= it.ptr_; }
  bool operator<(const Iterator& it) const { return ptr_ < it.ptr_; }
  bool operator>(const Iterator& it) const { return ptr_ > it.ptr_; }

  Iterator operator+(unsigned int n) const { return Iterator{ptr_ + n}; }

  Iterator operator-(unsigned int n) const { return Iterator{ptr_ - n}; }

  size_t operator-(Iterator& j) const {
    if (ptr_ > j.ptr_)
      return ptr_ - j.ptr_;
    else
      throw std::invalid_argument("");
  }

  T* operator[](unsigned int n) const { return ptr_ + n; }

  T const* operator->() { return &(*(*this)); }
  T const* operator->() const { return &(*(*this)); }

  Iterator& operator+=(unsigned int n) {
    ptr_ += n;
    return *this;
  }
  friend class MojVektor<T>;
};

template <typename T>
typename MojVektor<T>::Iterator operator+(
    int n, const typename MojVektor<T>::Iterator& it) {
  return it + n;
}

template <typename T>
MojVektor<T> subvector(typename MojVektor<T>::Iterator begin,
                       typename MojVektor<T>::Iterator end) {
  MojVektor<T> result{};
  for (auto i = begin; i != end; ++i) {
    result.push_back(*i);
  }
  return result;
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::begin() const {
  return arr_;
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::end() const {
  if (size_ != 0)
    return arr_ + size_;
  else
    return begin();
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::find(const T& el) const {
  if (size_ != 0) {
    for (auto i = begin(); i != end(); ++i)
      if (*i == el) return i;
  }
  return end();
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(
    typename MojVektor<T>::Iterator pos) {
  if (pos == end()) return end();
  for (auto i = pos; i != end();) {
    *i = *(i++);
  }
  --size_;
  return pos;
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(Iterator pos,
                                                     const T& el) {
  if (pos == end()) throw std::out_of_range("nemoguca pozicija");

  if (full()) realoc();
  for (auto i = end(); i != pos;) *i = *(i--);
  *pos = el;
  ++size_;
  return pos;
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(Iterator pos, T&& el) {
  if(pos==end()) throw std::out_of_range("");
  if (full()) realoc();
  for (auto i = end(); i != pos; --i) *i = *(i - 1);
  *pos = std::move(el);
  ++size_;
  return pos;
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::rbegin() const {
  return --end();
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::rend() const {
  return --begin();
}

template <typename T>
T* MojVektor<T>::data() {
  return arr_;
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator beginIt,
                                                    Iterator endIt) {
  if (begin() <= beginIt && beginIt < endIt && endIt <= end()) {
    size_t erased = endIt.ptr_ - beginIt.ptr_;
    if (endIt != end()) {
      for (auto i = beginIt; endIt != end(); ++i) {
        *i = *endIt;
        ++endIt;
      }
    }
    size_ -= erased;
    return beginIt;
  }
  return Iterator{nullptr};
}

template <typename T>
void MojVektor<T>::rotate() {
  auto i{begin()};
  auto j{end() - 1};
    for(auto k=0;k<size()/2;++k, ++i, --j){
      std::swap(*i,*j);
    }
}

// while(i!=j||i<j) ???

template <typename T>
void MojVektor<T>::rotate(Iterator beginIt, Iterator endIt) {
  if (begin() <= beginIt && beginIt < endIt && endIt <= end()) {
    size_t n=endIt-beginIt;
    --endIt;
    for(auto i=0;i<n/2;++i, ++beginIt, --endIt){
      std::swap(*beginIt,*endIt);
    }
  } else
    throw std::logic_error("");
}
