#ifndef SINGLY_LINKED_H
#define SINGLY_LINKED_H

template <typename T>
class SinglyLinkedList {
    public:
        SinglyLinkedList(T data = T());
        ~SinglyLinkedList();

    private:
        struct Node {
            Node* next = nullptr;
            T data = T();
        };
        Node* head_;

};

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(T data) {
    head_ = new Node;
    head_->data = data;
}

#endif