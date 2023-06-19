#include <iostream>

template <typename T>
class Heap
{
    size_t size_;
    size_t capacity_;
    T *data_;
    void reorderUp();
    void reorderDown(size_t, size_t);
    void reallocate();

public:
    Heap();
    Heap(const Heap &);
    Heap(Heap &&);
    Heap &operator=(const Heap &);
    Heap &operator=(Heap &&);
    ~Heap();

    template <typename F>
    void insert(F &&);
    bool empty() const;

    T &max();
    T removeMax();
    void prnt(size_t k) const;
    void prnt() const;
};

template <typename T>
bool Heap<T>::empty() const
{
    return !size_;
}

template <typename T>
void Heap<T>::prnt(size_t k) const
{
    std::cout << data_[k] << std::endl;
    if (k * 2 + 1 < size_)
        prnt(k * 2 + 1);
    if (k * 2 + 2 < size_)
        prnt(k * 2 + 2);
}

template <typename T>
void Heap<T>::prnt() const
{
    for (auto i = 0; i < size_; ++i)
        std::cout << data_[i] << std::endl;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Heap<T> &h)
{
    if (!h.empty())
        h.prnt(0);
    return out;
}

template <typename T>
Heap<T>::Heap() : size_(0), capacity_(50), data_(new T[capacity_]) {}

template <typename T>
Heap<T>::~Heap()
{
    delete[] data_;
}

template <typename T>
void Heap<T>::reallocate()
{
    capacity_ = capacity_ * 2;
    T *temp = new T[capacity_];
    std::swap(data_, temp);
    delete[] temp;
}

template <typename T>
template <typename F>
void Heap<T>::insert(F &&value)
{
    if (size_ == capacity_)
        reallocate();
    auto temp = size_;
    data_[size_++] = std::forward<F>(value);
    reorderUp();
}

template <typename T>
void Heap<T>::reorderUp()
{
    auto k = size_ - 1;
    while (k >= 0 && data_[k] > data_[k / 2])
    {
        std::swap(data_[k], data_[k / 2]);
        k /= 2;
    }
}

template <typename T>
Heap<T>::Heap(const Heap &other) : size_(other.size_), capacity_(other.capacity_), data_(new T[capacity_])
{
    std::copy(other.data_, other.data_ + size_, data_);
}

template <typename T>
Heap<T>::Heap(Heap &&other) : size_(other.size_), capacity_(other.capacity_), data_(other.data_)
{
    other.data_ = nullptr;
    other.size_ = other.capacity_ = 0;
}

template <typename T>
Heap<T> &Heap<T>::operator=(const Heap &other)
{
    if (this != &other)
    {
        size_ = other.size_;
        capacity_ = other.capacity_;
        delete[] data_;
        data_ = new T[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
    }
    return *this;
}

template <typename T>
Heap<T> &Heap<T>::operator=(Heap &&other)
{
    if (this != &other)
    {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = other.data_;
        other.size_ = other.capacity_ = 0;
        other.data_ = nullptr;
    }
    return *this;
}

template <typename T>
T &Heap<T>::max()
{
    if (empty())
        throw std::out_of_range("empty heap");
    return data_[0];
}

template <typename T>
T Heap<T>::removeMax()
{
    if (empty())
        throw std::logic_error("empty heap");
    std::swap(data_[0], data_[size_ - 1]);
    reorderDown(data_[0], --size_);
    return data_[size_];
}

template <typename T>
void Heap<T>::reorderDown(size_t k, size_t n)
{
    while (2 * k <= n)
    {
        int j = 2 * k;
        if (j < n && data_[j] < data_[j + 1])
            ++j;
        if (!(data_[k] < data_[j]))
            break;
        std::swap(data_[k], data_[j]);
        k = j;
    }
}
