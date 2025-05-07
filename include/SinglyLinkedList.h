#ifndef SINGLY_LINKED_H
#define SINGLY_LINKED_H

#include <stdexcept>

template <typename T>
class SinglyLinkedList {
    public:
        SinglyLinkedList();
        SinglyLinkedList(T data);
        ~SinglyLinkedList();

        SinglyLinkedList(const SinglyLinkedList&) = delete; // Apparently googletest creates copies of objects when testing, so this will prevent seg faults related to double delete.
        SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;
        
        void prepend(T value);
        void append(T value);
        // void remove(T value);

        T front() const;
        T end() const;
        bool contains(T value);

    private:
        struct Node {
            Node* next;
            T data;
            Node(T value, Node* nextNode = nullptr) : data(value), next(nextNode) {}
        };
        Node* head_;
        Node* tail_;

        // void deleteNextNode(Node* node);


};

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() {
    head_ = nullptr;
    tail_ = nullptr;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(T data) {
    head_ = new Node(data);
    head_->data = data;
    head_->next = nullptr;
    tail_ = head_;
    std::cout << "New head_: " << head_ << "\n";
    std::cout << "New tail_: " << tail_ << "\n";

}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    Node* current = head_;
    while (current) {
        std::cout << "Deleting node: " << current << "\n";
        Node* tmpNode = current;
        current = current->next;
        delete tmpNode;
    }
    head_ = tail_ = nullptr;
}

template <typename T>
void SinglyLinkedList<T>::prepend(T value) {
    Node* newNode = new Node(value, head_);
    if (head_ == nullptr) {
        tail_ = newNode;
    }
    head_ = newNode;
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
    return;
}

// template <typename T>
// void SinglyLinkedList<T>::remove(T value) {
//     Node* prev, current = head_;

//     while (current->next != nullptr && current->data != value) {
//         prev = current;
//         current = current->next;
//     }
//     if (current->data == value) {
//         prev->next = current->next;
//         if (current == tail_) {
//             tail_ = prev;
//         }
//         delete current;
//     }
//     return;
// }

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


// template <typename T>
// void SinglyLinkedList<T>::deleteNextNode(Node* node) {
//     Node* delNode = node->next;
//     node->next = delNode->next;
//     delete delNode;
//     return next;
// }

#endif