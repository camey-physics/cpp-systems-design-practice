#ifndef SHARED_PTR_H
#define SHARED_PTR_H

class SharedPtr {
    public:
        SharedPtr(int value = 0);
        SharedPtr(const SharedPtr& other);
        ~SharedPtr();
        SharedPtr& operator=(const SharedPtr& other);
        int& operator*();
        const int& operator*() const;

        int useCount() const;
        const int* get() const;

    private:
        int* ptr_ = nullptr;
        int* ref_count_ = nullptr;

        void incrementRefCount();
        void decrementAndCleanup();
};

#endif