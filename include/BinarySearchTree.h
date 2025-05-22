#ifndef BST_H
#define BST_H

#include <cassert>

template <typename T>
class BinarySearchTree {
    public:

    private:
        struct Node {
            T data;
            Node* left = nullptr;
            Node* right = nullptr;

            Node() = default;
            Node(const T& value) : data(value) {};
            Node(T&& value) : data(std::move(value)) {};
            // Consider adding perfect forwarding in the future
        };

};

#endif