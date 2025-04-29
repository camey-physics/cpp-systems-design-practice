#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <cassert>

template <typename T>
class SharedPtr {
    public:
        SharedPtr(T value = T());
        SharedPtr(const SharedPtr& other);
        ~SharedPtr();
        SharedPtr& operator=(const SharedPtr& other);
        T& operator*();
        const T& operator*() const;

        int useCount() const;
        const T* get() const;

    private:
        T* ptr_ = nullptr;
        int* ref_count_ = nullptr;

        void incrementRefCount();
        void decrementAndCleanup();
};

template <typename T>
void SharedPtr<T>::incrementRefCount() {
    if (ref_count_ == nullptr) {
        ref_count_ = new int;
        *ref_count_ = 1;
    }
    else {
        *ref_count_ += 1;
    }
};

template <typename T>
void SharedPtr<T>::decrementAndCleanup() {
    if (ref_count_ == nullptr) {
        assert((ptr_ == nullptr) == (ref_count_ == nullptr));
        return;
    }
    else if (*ref_count_ > 1) {
        *ref_count_ -= 1;
    }
    else {
        delete ptr_;
        delete ref_count_;
    }
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
    decrementAndCleanup();
}

template <typename T>
SharedPtr<T>::SharedPtr(T value) {
    ptr_ = new T(value);
    ref_count_ = new int;
    *ref_count_ = 1;
}

// Copy constructor for SharedPtr b = a; (a = other, b is being constructed)
template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) {
    ptr_ = other.ptr_;
    ref_count_ = other.ref_count_;
    incrementRefCount();
}

// Copy assignment operator (overload  =)
template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other){
    if (this == &other) {
        return *this;
    }
    decrementAndCleanup();

    ptr_ = other.ptr_;
    ref_count_ = other.ref_count_;
    incrementRefCount();
    return *this;
}

template <typename T>
int SharedPtr<T>::useCount() const {
    if (ref_count_ == nullptr) {
        return 0;
    }
    else {
        return *ref_count_;
    }
}

template <typename T>
const T* SharedPtr<T>::get() const {
    return ptr_;
}

template <typename T>
T& SharedPtr<T>::operator*() {
    assert(ptr_ != nullptr);
    return *ptr_;
}

template <typename T>
const T& SharedPtr<T>::operator*() const {
    assert(ptr_ != nullptr);
    return *ptr_; 
}

#endif