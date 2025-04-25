#include "SharedPtr.h"
#include <cassert>

void SharedPtr::incrementRefCount() {
    if (ref_count_ == nullptr) {
        ref_count_ = new int;
        *ref_count_ = 1;
    }
    else {
        *ref_count_ += 1;
    }
};

void SharedPtr::decrementAndCleanup() {
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

SharedPtr::~SharedPtr() {
    decrementAndCleanup();
}

SharedPtr::SharedPtr(int value) {
    ptr_ = new int(value);
    ref_count_ = new int;
    *ref_count_ = 1;
}

// Copy constructor for SharedPtr b = a; (a = other, b is being constructed)
SharedPtr::SharedPtr(const SharedPtr& other) {
    ptr_ = other.ptr_;
    ref_count_ = other.ref_count_;
    incrementRefCount();
}

// Copy assignment operator (overload  =)
SharedPtr& SharedPtr::operator=(const SharedPtr& other){
    if (this == &other) {
        return *this;
    }
    decrementAndCleanup();

    ptr_ = other.ptr_;
    ref_count_ = other.ref_count_;
    incrementRefCount();
    return *this;
}

int SharedPtr::useCount() const {
    if (ref_count_ == nullptr) {
        return 0;
    }
    else {
        return *ref_count_;
    }
}

const int* SharedPtr::get() const {
    return ptr_;
}

int& SharedPtr::operator*() {
    assert(ptr_ != nullptr);
    return *ptr_;
}
const int& SharedPtr::operator*() const {
    assert(ptr_ != nullptr);
    return *ptr_; 
}