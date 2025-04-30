#ifndef VECTOR_H
#define VECTOR_H

template <typename T>
class Vector {
    public:
        Vector(unsigned long size = 0, T value = T());
        ~Vector();
        Vector(const Vector& other);
        Vector& operator=(const Vector& other);

    private:
        T* ptr_ = nullptr;
        unsigned long size_ = 0;
};



#endif