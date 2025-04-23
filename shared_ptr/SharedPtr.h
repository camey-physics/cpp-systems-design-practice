#ifndef SHARED_PTR_H
#define SHARED_PTR_H

class SharedPtr {
    public:
        SharedPtr() {};
        SharedPtr(int size);
        SharedPtr(const SharedPtr& other);
        ~SharedPtr();
        SharedPtr& operator=(const SharedPtr& other);

    private:
        int* ptr_ = nullptr;
        int* ref_count_ = nullptr;
};

#endif