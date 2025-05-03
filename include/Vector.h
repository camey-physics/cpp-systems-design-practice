#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>

/*
To Do:
push_back
Can update copy operator so that if capacity_ > other.size_, ptr_ is not deleted.
*/

template <typename T>
class Vector {
    public:
        Vector(unsigned long size = 0, T value = T());
        ~Vector();
        Vector(const Vector& other);
        Vector& operator=(const Vector& other);
        T& operator[](unsigned long i);
        const T& operator[](unsigned long i) const;
        T& at(unsigned long i);
        const T& at(unsigned long i) const;
        void reserve(unsigned long capacity);
        void resize(unsigned long newSize);
        void pop_back();
        void push_back(T value);

        unsigned long size() const { return size_; };
        unsigned long capacity() const { return capacity_; };


    private:
        T* ptr_ = nullptr;
        unsigned long size_;
        unsigned long capacity_;

        // Helper functions
        void copyFrom(const Vector& other);
};

template <typename T>
Vector<T>::Vector(unsigned long size, T value) : size_(size), capacity_(size) {
    if (size_ > 0) {
        ptr_ = new T[size_];
        for (unsigned long i = 0; i < size_; ++i) {
            ptr_[i] = value;
        }
    }
    else {
        ptr_ = nullptr;
    }
}

template <typename T>
Vector<T>::~Vector() {
    delete[] ptr_;
}

template <typename T>
Vector<T>::Vector(const Vector& other) {
    copyFrom(other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this == &other) {
        return *this;
    }
    delete[] ptr_;
    copyFrom(other);
    return *this;
}

template<typename T>
T& Vector<T>::operator[](unsigned long i) {
    return ptr_[i];
}

template<typename T>
const T& Vector<T>::operator[](unsigned long i) const {
    return ptr_[i];
}

template <typename T>
T& Vector<T>::at(unsigned long i) {
    if (i < size_) {
        return ptr_[i];
    }
    else {
        throw std::out_of_range("Index out of range");
    }
}

template <typename T>
const T& Vector<T>::at(unsigned long i) const {
    if (i < size_) {
        return ptr_[i];
    }
    else {
        throw std::out_of_range("Index out of range");
    }
}

template <typename T>
void Vector<T>::reserve(unsigned long capacity) {
    if (capacity <= size_) {
        return;
    }
    T* tmpPtr = new T[capacity];
    for (unsigned long i = 0; i < size_; ++i) {
        tmpPtr[i] = ptr_[i];
    }
    delete[] ptr_;
    ptr_ = tmpPtr;
    capacity_ = capacity;

}

template <typename T>
void Vector<T>::resize(unsigned long newSize) {
    if (newSize > size_) {
        reserve(newSize);
        for (unsigned long i = size_; i < newSize; ++i) {
            ptr_[i] = T();
        }
    }    
    size_ = newSize;
}

template <typename T>
void Vector<T>::pop_back() {
    if (size_ > 0) {
        size_ -= 1;
    }
}

template <typename T>
void Vector<T>::push_back(T value) {
    if (capacity_ < 1 + size_) {
        reserve((1 + size_) *2);
    }
    size_ += 1;
    ptr_[size_ - 1] = value;
}

template <typename T>
void Vector<T>::copyFrom(const Vector<T>& other) {
    size_ = other.size_;
    capacity_ = size_;
    if (size_ > 0) {
        ptr_ = new T[size_];
        for (unsigned long i = 0; i < size_; ++i) {
            ptr_[i] = other.ptr_[i];
        }
    }
    else {
        ptr_ = nullptr;
    }
}

#endif