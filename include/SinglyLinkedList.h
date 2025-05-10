/*
Should replace head_ with dummy_ <- will require refactoring of several methods
Should add several functions:
pop_front()
pop_back()
insert(index, value)
erase(index)
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
        SinglyLinkedList(SinglyLinkedList&& other);
        SinglyLinkedList& operator=(SinglyLinkedList&& other);
        T& operator[](unsigned long ind);
        const T& operator[](unsigned long ind) const;
        
        void prepend(T value);
        void append(T value);
        void remove(T value);

        T front() const;
        T end() const;
        bool contains(T value);
        void clear();

        unsigned long size() const {return size_;}

    private:
        struct Node {
            Node* next;
            T data;
            Node(T value, Node* nextNode = nullptr) : data(value), next(nextNode) {}
        };
        Node* head_;
        Node* tail_;
        unsigned long size_;

        void copy(const SinglyLinkedList& other);

};

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(T data) {
    head_ = new Node(data);
    head_->data = data;
    head_->next = nullptr;
    tail_ = head_;
    size_ = 1;
}

template <typename T>
void SinglyLinkedList<T>::clear() {
    Node* current = head_;
    while (current) {
        Node* tmpNode = current;
        current = current->next;
        delete tmpNode;
    }
    head_ = tail_ = nullptr;
    size_ = 0;
}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    clear();
}

template <typename T>
void SinglyLinkedList<T>::copy(const SinglyLinkedList<T>& other) {
    if (other.head_ == nullptr) {
        head_ = tail_ = nullptr;
        size_ = 0;
        return;
    }
    head_ = new Node(other.head_->data);
    size_ = 1;
    Node* current = head_;
    Node* otherCurrent = other.head_;
    while (otherCurrent->next) {
        otherCurrent = otherCurrent->next;
        current->next = new Node(otherCurrent->data);
        current = current->next;
        size_++;
    }
    tail_ = current;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other) {
    head_ = tail_ = nullptr;
    size_ = 0;
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
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T>&& other) {
    this->head_ = other.head_;
    this->tail_ = other.tail_;
    this->size_ = other.size_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T>&& other) {
    this->clear();
    this->head_ = other.head_;
    this->tail_ = other.tail_;
    this->size_ = other.size_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
    return *this;
}

template <typename T>
T& SinglyLinkedList<T>::operator[](unsigned long ind){
    if (ind >= size_) {
        throw std::out_of_range("Index out of bounds");
    }
    Node* current = head_;
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
    Node* current = head_;
    for (unsigned long i = 0; i < ind; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
void SinglyLinkedList<T>::prepend(T value) {
    Node* newNode = new Node(value, head_);
    if (head_ == nullptr) {
        tail_ = newNode;
    }
    head_ = newNode;
    size_++;
    return;
}

template <typename T>
void SinglyLinkedList<T>::append(T value) {
    if (head_ == nullptr) {
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
    Node* current = head_;
    Node* prev;

    while (current != nullptr) {
        if (current->data == value) {
            if (current == head_) {
                if (current == tail_) {
                    head_ = nullptr;
                    tail_ = nullptr;

                }
                else {
                    head_ = current->next;
                }
            }
            else if (current == tail_) {
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
T SinglyLinkedList<T>::front() const {
    if (head_ != nullptr) {
        return head_->data;
    }
    else {
        throw std::runtime_error("List is empty");
    }
}

template <typename T>
T SinglyLinkedList<T>::end() const {
    if (tail_ != nullptr) {
        return tail_->data;
    }
    else {
        throw std::runtime_error("List is empty");
    }
}

template <typename T>
bool SinglyLinkedList<T>::contains(T value) {
    Node* current = head_;
    while (current) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

#endif