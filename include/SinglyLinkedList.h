/*
Should replace head_ with dummy_ <- will require refactoring of several methods
Should add several functions:
comparison (==, !=)
*/

#ifndef SINGLY_LINKED_H
#define SINGLY_LINKED_H

#include <stdexcept>

template <typename T>
class SinglyLinkedList {
    public:
        SinglyLinkedList();
        SinglyLinkedList(T data);
        ~SinglyLinkedList();

        SinglyLinkedList(const SinglyLinkedList& other);
        SinglyLinkedList& operator=(const SinglyLinkedList& other);
        SinglyLinkedList(SinglyLinkedList&& other) noexcept;
        SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept;
        T& operator[](unsigned long ind);
        const T& operator[](unsigned long ind) const;
        
        void prepend(T value);
        void append(T value);
        void remove(T value);
        void erase(unsigned long ind);
        T pop_front();
        T pop_back();
        void insert(unsigned long ind, T value);

        T front() const;
        T end() const;
        bool contains(T value);
        void clear();

        unsigned long size() const {return size_;}
        bool empty() const { return size_ == 0; }

    private:
        struct Node {
            Node* next;
            T data;
            Node(T value, Node* nextNode = nullptr) : data(value), next(nextNode) {}
        };
        Node* dummy_;
        Node* tail_;
        unsigned long size_;

        void copy(const SinglyLinkedList& other);
        T erase_and_return(unsigned long ind);

};

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() : dummy_(new Node(T())), tail_(nullptr), size_(0) {}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(T data) : SinglyLinkedList() {
    dummy_->next = new Node(data, nullptr);
    tail_ = dummy_->next;
    size_ = 1;
}

template <typename T>
void SinglyLinkedList<T>::clear() {
    Node* current = dummy_->next;
    while (current) {
        Node* tmpNode = current;
        current = current->next;
        delete tmpNode;
    }
    dummy_->next = tail_ = nullptr;
    size_ = 0;
}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    clear();
    delete dummy_;
}

template <typename T>
void SinglyLinkedList<T>::copy(const SinglyLinkedList<T>& other) {
    Node* otherCurrent = other.dummy_;
    Node* current = dummy_;
    size_ = 0;

    while (otherCurrent->next) {
        otherCurrent = otherCurrent->next;
        current->next = new Node(otherCurrent->data);
        current = current->next;
        size_++;
    }
    tail_ = current;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other) : SinglyLinkedList() {
    copy(other);
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other) {
    if (this == &other) {
        return *this;
    }
    clear();
    copy(other);
    return *this;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T>&& other) noexcept : SinglyLinkedList() {
    this->dummy_->next = other.dummy_->next;
    this->tail_ = other.tail_;
    this->size_ = other.size_;
    other.dummy_->next = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T>&& other) noexcept {
    this->clear();
    this->dummy_->next = other.dummy_->next;
    this->tail_ = other.tail_;
    this->size_ = other.size_;
    other.dummy_->next = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
    return *this;
}

template <typename T>
T& SinglyLinkedList<T>::operator[](unsigned long ind){
    if (ind >= size_) {
        throw std::out_of_range("Index out of bounds");
    }
    Node* current = dummy_->next;
    for (unsigned long i = 0; i < ind; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
const T& SinglyLinkedList<T>::operator[](unsigned long ind) const{
    if (ind >= size_) {
        throw std::out_of_range("Index out of bounds");
    }
    Node* current = dummy_->next;
    for (unsigned long i = 0; i < ind; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
void SinglyLinkedList<T>::prepend(T value) {
    Node* newNode = new Node(value, dummy_->next);
    dummy_->next = newNode;
    if (tail_ == nullptr) {
        tail_ = newNode;
    }
    size_++;
    return;
}

template <typename T>
void SinglyLinkedList<T>::append(T value) {
    if (tail_ == nullptr) {
        SinglyLinkedList<T>::prepend(value);
        return;
    }
    Node* newNode = new Node(value);
    tail_->next = newNode;
    tail_ = newNode;
    size_++;
    return;
}

template <typename T>
void SinglyLinkedList<T>::remove(T value) {
    Node* current = dummy_->next;
    Node* prev = dummy_;

    while (current) {
        if (current->data == value) {
            if (current == tail_) {
                tail_ = prev;
                prev->next = nullptr;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            size_--;
            return;
        }
        prev = current;
        current = current->next;
    }
    return;
}

template <typename T>
T SinglyLinkedList<T>::erase_and_return(unsigned long ind) {
    if (ind >= size_) {
        throw std::out_of_range("Index is out of bounds");
    }
    Node* current = dummy_->next;
    Node* prev = dummy_;
    unsigned long cnt = 0;
    while (cnt < ind) {
        prev = current;
        current = current->next;
        cnt++;
    }
    prev->next = current->next;
    T data = current->data;
    if (tail_ == current) {
        tail_ = prev;
    }
    delete current;
    size_--;
    return data;
}


template <typename T>
void SinglyLinkedList<T>::erase(unsigned long ind) {
    (void) erase_and_return(ind);
}

template <typename T>
T SinglyLinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return erase_and_return(0);
}

template <typename T>
T SinglyLinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return erase_and_return(size_ - 1);
}

template <typename T>
void SinglyLinkedList<T>::insert(unsigned long ind, T value) {
    if (ind > size_) {
        throw std::out_of_range("Index larger than list size");
    }
    else if (ind == size_) {
        append(value);
        return;
    }
    Node* current = dummy_->next;
    Node* prev = dummy_;
    unsigned long cnt = 0;
    while (cnt < ind) {
        prev = current;
        current = current->next;
        cnt++;
    }
    Node* new_node = new Node(value, current);
    prev->next = new_node;
    size_++;
}

template <typename T>
T SinglyLinkedList<T>::front() const {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return dummy_->next->data;
}

template <typename T>
T SinglyLinkedList<T>::end() const {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return tail_->data;
}

template <typename T>
bool SinglyLinkedList<T>::contains(T value) {
    Node* current = dummy_->next;
    while (current) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

#endif