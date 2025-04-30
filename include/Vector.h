#ifndef VECTOR_H
#define VECTOR_H

/*
To Do:
push_back, pop_back
operator[] for element access
Possibly resize or reserve for memory management.
*/

template <typename T>
class Vector {
    public:
        Vector(unsigned long size = 0, T value = T());
        ~Vector();
        Vector(const Vector& other);
        Vector& operator=(const Vector& other);

    private:
        T* ptr_ = nullptr;
        unsigned long size_;
};

template <typename T>
Vector<T>::Vector(unsigned long size, T value) : size_(size) {
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

#endif