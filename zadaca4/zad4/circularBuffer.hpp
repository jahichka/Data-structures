#include <stdexcept>
#include <vector>

template <typename T> class circularBuffer {
private:
  std::size_t size_{0};
  std::size_t capacity{0};
  std::vector<T> buffer;
  std::size_t first;
  std::size_t last;
  bool full() { return size_ == capacity; }

public:
  circularBuffer() {}
  circularBuffer(const circularBuffer& other)
      : buffer(other.buffer), size_(other.size_),
        capacity(other.capacity) {}
    circularBuffer(circularBuffer&& other)
      : buffer(std::move(other.buffer)), size_(other.size_),
        capacity(other.capacity) {
            other.size_=other.capacity=0;
            other.buffer.clear();
        }

    circularBuffer<T>& operator =(const circularBuffer& other){
        buffer.clear();
        buffer=other.buffer;
        size_=other.size_;
        capacity=other.capacity;
        return *this;
    }

    circularBuffer<T>& operator=(circularBuffer&& other){
        buffer.clear();
        buffer=std::move(other.buffer);
        size_=other.size_;
        capacity=other.capacity;
        return *this;
    }
    
  circularBuffer(std::size_t max) : capacity(max), buffer(max, 0) {}


  ~circularBuffer() { size_ = capacity = 0; }

  bool empty() { return !size_; }
  std::size_t size() { return size_; }

  const T &front() { 
    if(!empty()) return buffer[0];
    else throw std::out_of_range("empty queue");
    }
  const T &front() const { 
    if(!empty()) return buffer[0]; 
    else throw std::out_of_range("empty queue");
    }
  const T &back() { 
    if(!empty()) return buffer[size_ - 1];
    else throw std::out_of_range("empty queue");
     }
  const T &back() const { 
    if(!empty()) return buffer[size_ - 1];
    else throw std::out_of_range("empty queue"); }

  template <typename F> void push(F &&elem) {
    if (full())
      throw std::out_of_range("full buffer");
    else {
      last = (last + 1) % capacity;
      buffer[last] = std::forward<F>(elem);
      ++size_;
    }
  }

  T pop() {
    if (empty())
      throw std::out_of_range("empty buffer");
    else {
      int to_pop = first;
      first = (first + 1) % capacity;
      --size_;
      return std::move(buffer[to_pop]);
    }
  }
};