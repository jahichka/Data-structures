#pragma once
#include <iostream>

template <typename K, typename V>
struct Node
{
    std::pair<K, V> value;
    Node *left = nullptr;
    Node *right = nullptr;
    /* data */
    template <typename F>
    Node(K key, F &&value) : value(std::pair<K, V>(key, value)) {}
};

template <typename K, typename V>
class Map
{
    Node<K, V> *root_ = nullptr;
    size_t size_ = 0;
    void insertSubtree(Node<K, V> *other);

public:
    void prnt();

    Map();
    Map(const Map &);
    Map(Map &&);
    Map &operator=(const Map &);
    Map &operator=(Map &&);
    ~Map();

    bool empty() const;
    size_t size() const;

    V &at(const K &);
    const V &at(const K &) const;

    V *find(const K &);
    const V *find(const K &) const;

    V &operator[](const K &);

    template <typename F>
    void insert(const K &, F &&);

    bool erase(const K &);
    void clear();
};

template <typename K, typename V>
Map<K, V>::Map() : root_{nullptr}, size_{0} {}

template <typename K, typename V>
void Map<K, V>::insertSubtree(Node<K, V> *other)
{
    if (other == nullptr)
        return;
    insert(other->value.first, other->value.second);
    insertSubtree(other->left);
    insertSubtree(other->right);
}

template <typename K, typename V>
Map<K, V>::Map(const Map &other) : size_(other.size_)
{
    insertSubtree(other.root_);
}

template <typename K, typename V>
Map<K, V>::Map(Map &&other) : size_(other.size_), root_(std::move(other.root_))
{
    other.root_ = nullptr;
    other.size_ = 0;
}

template <typename K, typename V>
Map<K, V> &Map<K, V>::operator=(const Map<K, V> &other)
{
    clear();
    insertSubtree(other.root_);
    size_ = other.size_;
    return *this;
}

template <typename K, typename V>
void deleteSubtree(Node<K, V> *node)
{
    if (!node)
        return;
    if (node->left)
        deleteSubtree(node->left);
    if (node->right)
        deleteSubtree(node->right);
    delete node;
}

template <typename K, typename V>
void Map<K, V>::clear()
{
    if (!root_)
    {
        return;
    }
    deleteSubtree(root_);
    size_ = 0;
    root_ = nullptr;
}

template <typename K, typename V>
Map<K, V> &Map<K, V>::operator=(Map &&other)
{
    clear();
    root_ = other.root_;
    size_ = other.size_;
    other.root_ = nullptr;
    other.size_ = 0;
    return *this;
}

template <typename K, typename V>
Map<K, V>::~Map()
{
    clear();
}

template <typename K, typename V>
bool Map<K, V>::empty() const
{
    return !size_;
}

template <typename K, typename V>
size_t Map<K, V>::size() const { return size_; }

template <typename K, typename V>
V *Map<K, V>::find(const K &other)
{
    auto temp = root_;
    while (!temp)
    {
        if (temp->value.first == other)
            return &(temp->value.second);
        else if (other > temp->value.first)
            temp = temp->right;
        else
            temp = temp->left;
    }
    return nullptr;
}

template <typename K, typename V>
const V *Map<K, V>::find(const K &other) const
{
    auto temp = root_;
    while (!temp)
    {
        if (temp->value.first == other)
            return &(temp->value.second);
        else if (other > temp->value.first)
            temp = temp->right;
        else
            temp = temp->left;
    }
    return nullptr;
}

template <typename K, typename V>
V &Map<K, V>::at(const K &other)
{
    auto result = find(other);
    if (!result)
        throw std::out_of_range("no key");
    else
        return *result;
}

template <typename K, typename V>
const V &Map<K, V>::at(const K &other) const
{
    auto result = find(other);
    if (!result)
        throw std::out_of_range("no key");
    else
        return *result;
}

template <typename K, typename V>
V &Map<K, V>::operator[](const K &key)
{
    if (!find(key))
        insert(key, V());
    return at(key);
}

template <typename K, typename V>
template <typename F>
void Map<K, V>::insert(const K &key, F &&value)
{
    Node<K, V> **temp = &root_;

    while (*temp != nullptr)
    {
        if ((*temp)->value.first == key)
            throw std::out_of_range("existing key");
        else if ((*temp)->value.first > key)
            temp = &((*temp)->left);
        else
            temp = &((*temp)->right);
    }

    *temp = new Node<K, V>(key, std::forward<F>(value));
    ++size_;
}

template <typename K, typename V>
void print(Node<K, V> *node)
{
    std::cout << node->value.first << std::endl;
    if (node->left)
        print(node->left);
    if (node->right)
        print(node->right);
}

template <typename K, typename V>
void Map<K, V>::prnt()
{
    print(root_);
}

template <typenameK, typename V>
bool Map<K, V>::erase(const K &key)
{
    if (empty())
        throw std::logic_error("empty bst");
    auto *temp = &find(key);
    if (*temp == nullptr)
        return false;

    if (*temp->left == nullptr && *temp->right == nullptr)
    {
        delete *temp;
        *temp = nullptr;
    }
    else if(*temp->left==nullptr){
        auto ptr=*temp;
        *temp=*temp->right;
        delete ptr;
    }
    else if(*temp->right==nullptr){
        auto ptr=*temp;
        *temp=*temp->left;
        delete ptr;
    }
    else{
        Node<K,V>* previous=nullptr;
        auto current=*temp->left;
        while(current->right!=nullptr){
            previous=current;
            current=current->right;
        }
        *temp->first=current->first;
        if(previous!=nullptr)
        previous->right=current->left;
        else{
            e->left=current->left;
        }
        delete current;
        --size_;
    }
}