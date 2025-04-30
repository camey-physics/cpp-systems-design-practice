#ifndef VECTOR_H
#define VECTOR_H

/*
To Do:
push_back, pop_back
operator[]
size()
at()
Possibly resize or reserve for memory management.
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

        unsigned long size() const { return size_; };


    private:
        T* ptr_ = nullptr;
        unsigned long size_;

        // Helper functions
        void copyFrom(const Vector& other);
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
void Vector<T>::copyFrom(const Vector<T>& other) {
    size_ = other.size_;
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