#pragma once

#include <functional>
#include <iterator>
#include <ostream>
#include <stdexcept>


template <typename T> class DoubleLinkedList {
public:
  class Iterator;
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
  struct Node {
    Node *prev{};
    Node *next{};
    T data;
    Node():prev{nullptr},next{nullptr},data(T()){}
    Node(Node* a, Node* b):prev{a},next{b}{}
    Node(Node* a, Node* b, T element):prev(a),next(b),data(element){}
  };

  void dealoc();
  Node *head_{};
  Node *tail_{};
  size_t size_{};
  Node* sentinel_=new Node{nullptr,nullptr};
};

template <typename T>
class DoubleLinkedList<T>::Iterator : public std::bidirectional_iterator_tag {

public:
  Iterator() : ptr_{nullptr} {}
  Iterator(const Iterator &other) : ptr_(other.ptr_) {}
  Iterator(Iterator &&other) : ptr_(other.ptr_) { other.ptr_ = nullptr; }
  Iterator &operator=(const Iterator &other) {
    if (this != &other)
      ptr_ = other.ptr_;
    return *this;
  }
  Iterator &operator=(Iterator &&other) {
    return *this = Iterator(std::move(other.ptr_));
  }
  ~Iterator() { ptr_ = nullptr; }
  Iterator(Node* p) : ptr_{p} {}

  Iterator &operator++() {
    ++ptr_;
    ptr_ = ptr_->next;

    return *this;
  }

  Iterator operator++(int) {
    auto temp = *this;
    ptr_ = ptr_->next;
    return temp;
  }

  Iterator &operator--() {
    --ptr_;
    ptr_ = ptr_->prev;
    return *this;
  }

  Iterator operator--(int) {
    auto temp = *this;
    ptr_ = ptr_->prev;
    return temp;
  }

  Node &operator*() { return *ptr_; }

  Node *operator->() { return ptr_; }

  bool operator==(Iterator other) { return ptr_ == other.ptr_; }
  bool operator!=(Iterator other) { return !(*this == other); }

private:
  Node *ptr_{};
};

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList()
    : size_(0), sentinel_(), head_(),
      tail_() {
        sentinel_->next=sentinel_;
        sentinel_->prev=sentinel_;
        head_=tail_=sentinel_;
      }

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T> &other) {
  sentinel_->next = sentinel_->prev = sentinel_;
  for (auto i = other.begin(); i != other.end(); ++i) {
    push_back(*i);
  }
  sentinel_->next = head_;
  sentinel_->prev = tail_;
  sentinel_->prev->next = sentinel_->next->prev = sentinel_;
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T> &&other)
    : size_{other.size_}, sentinel_{other.sentinel_}, head_{other.head_},
      tail_{other.tail_} {
  sentinel_->prev->next = sentinel_->next->prev = sentinel_;
  other.head_=other.tail_=sentinel_;
  other.size_=0;
}

template <typename T> DoubleLinkedList<T>::~DoubleLinkedList() { 
    clear(); 
    delete sentinel_;
    head_=tail_=nullptr;}

template <typename T>
DoubleLinkedList<T> &
DoubleLinkedList<T>::operator=(const DoubleLinkedList<T> &other) {
  clear();
  sentinel_->next = sentinel_->prev = sentinel_;
  for (auto i = other.begin(); i != other.end(); ++i) {
    push_back(*i);
  }
  sentinel_->next = head_;
  sentinel_->prev = tail_;
  sentinel_->prev->next = sentinel_->next->prev = sentinel_;
}

template <typename T>
DoubleLinkedList<T> &
DoubleLinkedList<T>::operator=(DoubleLinkedList<T> &&other) {
  size_ = other.size_;
  sentinel_ = other.sentinel_;
  head_ = other.head_;
  tail_ = other.tail_;
  sentinel_->prev->next = sentinel_->next->prev = sentinel_;
}

template <typename T>
DoubleLinkedList<T> &DoubleLinkedList<T>::push_back(const T &element) {
  if (size_ == 0) {
    sentinel_->next = sentinel_->prev = new Node{sentinel_, sentinel_, element};
    head_ = tail_ = sentinel_->next;
  } else {
    auto temp = new Node{sentinel_->previous, sentinel_, element};
    sentinel_->prev->next = temp;
    sentinel_->prev = temp;
  }
  ++size_;
  return *this;
}

template <typename T>
DoubleLinkedList<T> &DoubleLinkedList<T>::push_back(T &&element) {
  if (size_ == 0) {
    sentinel_->next = sentinel_->prev =
        new Node{sentinel_, sentinel_, std::move(element)};
    head_ = tail_ = sentinel_->next;
  } else {
    auto temp = new Node(sentinel_->prev, sentinel_, std::move(element));
    sentinel_->prev->next = temp;
    sentinel_->prev = temp;
  }
  ++size_;
  return *this;
}

template <typename T>
DoubleLinkedList<T> &DoubleLinkedList<T>::push_front(const T &element) {
  if (size_ == 0) {
    sentinel_->next = sentinel_->prev = new Node{sentinel_, sentinel_, element};
    head_ = tail_ = sentinel_->next;
  } else {
    auto temp = new Node{sentinel_, sentinel_->next, element};
    sentinel_->next->prev = temp;
    sentinel_->next = temp;
  }
  ++size_;
  return *this;
}

template <typename T>
DoubleLinkedList<T> &DoubleLinkedList<T>::push_front(T &&element) {
  if (size_ == 0) {
    sentinel_->next = sentinel_->prev =
        new Node{sentinel_, sentinel_, std::move(element)};
    head_ = tail_ = sentinel_->next;
  } else {
    auto temp = new Node{sentinel_, sentinel_->next, std::move(element)};
    sentinel_->next->prev = temp;
    sentinel_->next = temp;
  }
  ++size_;
  return *this;
}

template <typename T> DoubleLinkedList<T> &DoubleLinkedList<T>::pop_back() {
  auto temp = sentinel_->prev;
  sentinel_->prev = sentinel_->prev->prev;
  sentinel_->prev->next = sentinel_;
  temp->prev = temp->next = nullptr;
  delete temp;
  --size_;
  return *this;
}

template <typename T> DoubleLinkedList<T> &DoubleLinkedList<T>::pop_front() {
  auto temp = sentinel_->next;
  sentinel_->next = sentinel_->next->next;
  sentinel_->next->prev = sentinel_;
  temp->prev = temp->next = nullptr;
  delete temp;
  --size_;
  return *this;
}

template <typename T> size_t DoubleLinkedList<T>::size() const { return size_; }

template <typename T> bool DoubleLinkedList<T>::empty() const { return !size_; }

template <typename T> T &DoubleLinkedList<T>::front() {
  return sentinel_->next->data;
}

template <typename T> T &DoubleLinkedList<T>::back() {
  return sentinel_->previous->data;
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::begin() const{return Iterator{head_};}

template<typename T>
typename  DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::end() const{return Iterator{sentinel_};}

template<typename T>
  const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::cbegin() const{return begin();}

  template<typename T>
  const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::cend() const{return end();}

  template<typename T>
  typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rbegin() const{return Iterator{sentinel_};}

  template<typename T>
  typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rend() const{return Iterator{tail_};}

template<typename T>
  const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rcbegin() const{return rbegin();}

  template<typename T>
  const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rcend() const{return rend();}

  template<typename T>
  void DoubleLinkedList<T>::clear(){
    if(size_==0) return;
    for(auto i=sentinel_->next;i!=sentinel_;){
        i=i->next;
        delete i->prev;
    }
    sentinel_->prev=sentinel_->next=head_=tail_=sentinel_;
    size_=0;
  }

template<typename T>
  typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::insert(typename DoubleLinkedList<T>::Iterator pos, const T &element){
    pos->prev=pos->prev->next=new Node{pos,pos->next,element};
        ++size_;
    return pos;
  }

template<typename T>
  typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(Iterator pos){
    pos->prev->next=pos->next;
    pos->next->prev=pos->prev;
    delete pos.p_;
    --size_;
  }

  template<typename T>
  typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(Iterator beginIt, Iterator endIt){
    Iterator b{beginIt->prev};
    if(size_==0) return sentinel_;
    for(auto i=beginIt;i!=endIt;){
        i=i->next;
        delete i->prev;
        --size_;
    }
    b->next=endIt;
    endIt->prev=b;
    return endIt;
  }

  template <typename T>
  void DoubleLinkedList<T>::remove_if(std::function<bool(const T &)> &&p){
    for(auto i=sentinel_->next;i!=sentinel_;){
        if(p(i->data)) {
            i=i->next;
            erase(i->prev);
        }
        i=i->next;
    }
  }

  //void reverse();
  //Iterator find(const T &element) const;