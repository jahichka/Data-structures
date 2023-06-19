#pragma once

#include <exception>
#include <functional>
#include <iostream>
#include <iterator>
#include <stdexcept>

template <typename T> struct Node {
  Node *prev{};
  Node *next{};
  T data;
  Node(const T &element) : data{element}, prev{nullptr}, next{nullptr} {}
};

template <typename T> class DoubleLinkedList {
public:
  class Iterator {
  private:
    Node<T> *p_ = nullptr;

  public:
    Iterator() : p_{nullptr} {}
    Iterator(Node<T> *x) : p_{x} {}
    Iterator(const Iterator &o) : p_{o.p_} {};
    Iterator(Iterator &&o) : p_{o.p_} { o.p_ = nullptr; };
    Iterator &operator=(const Iterator &o) { p_ = o.p_; }
    Iterator &operator=(Iterator &&o) {
      p_ = o.p_;
      o.p_ = nullptr;
    }

    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Node<T>;
    using pointer = value_type *;
    using reference = value_type &;

    T &operator*() const { return p_->data; }
    Iterator &operator++() {
      p_ = p_->next;
      return *this;
    }
    Iterator operator++(int) {
      auto temp = p_;
      p_ = p_->next;
      return temp;
    }
    Iterator &operator--() {
      p_ = p_->prev;
      return *this;
    }
    Iterator operator--(int) {
      auto temp = p_;
      p_ = p_->prev;
      return temp;
    }
    Node<T> *node() { return p_; };

    bool operator==(Iterator o) const { return p_ == o.p_; }
    bool operator!=(Iterator o) const { return p_ != o.p_; }

    T *operator->() const { return &p_->data; }
  };
  DoubleLinkedList();
  DoubleLinkedList(const DoubleLinkedList &);
  DoubleLinkedList(DoubleLinkedList &&);
  DoubleLinkedList &operator=(const DoubleLinkedList &);
  DoubleLinkedList &operator=(DoubleLinkedList &&);
  ~DoubleLinkedList();

  DoubleLinkedList &push_back(const T &);
  DoubleLinkedList &push_front(const T &);
  DoubleLinkedList &push_back(T &&);
  DoubleLinkedList &push_front(T &&);
  DoubleLinkedList &pop_front();
  DoubleLinkedList &pop_back();

  bool empty() const;
  size_t size() const;
  T &front();
  T &back();
  void ispis();
  Iterator begin() const;
  Iterator end() const;
  const Iterator cbegin() const;
  const Iterator cend() const;
  Iterator rbegin() const;
  Iterator rend() const;
  const Iterator rcbegin() const;
  const Iterator rcend() const;
  void clear();
  Iterator insert(Iterator pos, const T &element);
  Iterator erase(Iterator pos);
  Iterator erase(Iterator beginIt, Iterator endIt);
  void remove_if(std::function<bool(const T &)> &&p);
  void reverse();
  Iterator find(const T &element) const;

private:
  void dealoc();
  Node<T> *head_{nullptr};
  Node<T> *tail_{nullptr};
  size_t size_{0};
};

template <typename T> DoubleLinkedList<T>::DoubleLinkedList() {}

template <typename T>
DoubleLinkedList<T> &DoubleLinkedList<T>::push_back(const T &element) {
  ++size_;
  if (size_ == 0)
    head_ = tail_ = new Node<T>{element};
  else {
    tail_->next = new Node<T>{element};
    tail_->next->prev = tail_;
    tail_ = tail_->next;
  }
  return *this;
}

template <typename T>
DoubleLinkedList<T> &DoubleLinkedList<T>::push_front(const T &element) {
  ++size_;
  if (size_ == 0)
    head_ = tail_ = new Node<T>{element};
  else {
    head_->prev = new Node<T>{element};
    head_->prev->next = tail_;
    head_ = head_->next;
  }
  return *this;
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T> &other) {
  if (other.size_ == 0) {
    size_ = 0;
    head_ = tail_ = nullptr;
  }
  head_ = tail_ = new Node<T>{other.head_->data};
  ++size_;
  if (other.head_ != other.tail_) {
    for (auto i = head_->next; i != nullptr; i = i->next) {
      push_back(i->data);
    }
  }
}

template <typename T>
DoubleLinkedList<T> &DoubleLinkedList<T>::push_front(T &&element) {
  ++size_;
  if (size_ == 0)
    head_ = tail_ = new Node<T>{std::move(element)};
  else {
    head_->prev = new Node<T>{element};
    head_->prev->next = tail_;
    head_ = head_->next;
  }
  return *this;
}

template <typename T>
DoubleLinkedList<T> &DoubleLinkedList<T>::push_back(T &&element) {
  ++size_;
  if (size_ == 0)
    head_ = tail_ = new Node<T>{std::move(element)};
  else {
    tail_->next = new Node<T>{element};
    tail_->next->prev = tail_;
    tail_ = tail_->next;
  }
  return *this;
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T> &&other) {
  size_ = other.size_;
  other.size_ = 0;
  head_ = other.head_;
  tail_ = other.tail_;
  other.head_ = other.tail_ = nullptr;
}

template <typename T> void DoubleLinkedList<T>::clear() {
  while (head_ != tail_) {
    Node<T> *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  delete tail_;
  size_ = 0;
  head_ = nullptr;
  tail_ = nullptr;
}
template <typename T> DoubleLinkedList<T>::~DoubleLinkedList() {
  clear();
  head_ = tail_ = nullptr;
  size_ = 0;
}

template <typename T> bool DoubleLinkedList<T>::empty() const {
  return (size_ == 0);
}

template <typename T> size_t DoubleLinkedList<T>::size() const { return size_; }

template <typename T> T &DoubleLinkedList<T>::back() {
  if (empty())
    throw std::out_of_range("");
  return tail_->data;
}

template <typename T> T &DoubleLinkedList<T>::front() {
  if (empty())
    throw std::out_of_range("");
  return head_->data;
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::begin() const {
  return Iterator{head_};
}

template <typename T>
const typename DoubleLinkedList<T>::Iterator
DoubleLinkedList<T>::cbegin() const {
  return Iterator{head_};
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::end() const {
  return nullptr;
}

template <typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::cend() const {
  return nullptr;
}

template <typename T>
DoubleLinkedList<T> &
DoubleLinkedList<T>::operator=(const DoubleLinkedList<T> &o) {
  clear();
  if (o.empty())
    return *this;
  head_ = tail_ = new Node<T>{o.head_->data};
  ++size_;
  if (o.head_ != o.tail_) {
    for (auto i = head_->next; i != nullptr; i = i->next) {
      push_back(i->data);
    }
  }
}

template <typename T>
DoubleLinkedList<T> &
DoubleLinkedList<T>::operator=(DoubleLinkedList<T> &&other) {
  clear();
  size_ = other.size_;
  other.size_ = 0;
  head_ = other.head_;
  tail_ = other.tail_;
  other.head_ = other.tail_ = nullptr;
}


template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_back(){
  if(empty()) throw std::out_of_range("");
  if(size()==1){
    delete head_;
    head_=tail_=nullptr;
  }
  else{
  auto temp=tail_;
  tail_=tail_->prev;
  tail_->next=nullptr;
  delete temp;
  }
  --size_;
  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_front(){
  if(empty()) throw std::out_of_range("");
  if(size()==1){
    delete head_;
    head_=tail_=nullptr;
  }
  else{
  auto temp=head_;
  head_=head_->prev;
  head_->prev=nullptr;
  delete temp;
  }
  --size_;
  return *this;
}
