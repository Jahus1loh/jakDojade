#pragma once
#include <iostream>
using namespace std;

template <typename T>
class ownVector {
private:
    T* arr;
    int capacity;
    int size;
public:
    // default constructor
    ownVector() {
        arr = new T[1];
        capacity = 1;
        size = 0;
    }

    // copy constructor
    ownVector(const ownVector& src) {
        arr = new T[src.capacity];
        capacity = src.capacity;
        size = src.size;
        for (int i = 0; i < size; ++i) {
            arr[i] = src.arr[i];
        }
    }

    // move constructor
    ownVector(ownVector&& other) : arr(other.arr), capacity(other.capacity), size(other.size) {
        other.arr = nullptr;
        other.capacity = 0;
        other.size = 0;
    }

    // deconstructor
    ~ownVector() {
        delete[] arr;
    }

    // copy assignment operator
    ownVector& operator=(ownVector other) {
        other.swap(*this);
        return *this;
    }
    
    void swap(ownVector& other) {
        T* ptr = arr;
        arr = other.arr;
        other.arr = ptr;

        int cap = capacity;
        capacity = other.capacity;
        other.capacity = cap;
        
        int sz = size;
        size = other.size;
        other.size = sz;
    }

    void push(const T& data) {
        if (size == capacity) {
            T* temp = new T[2 * capacity];
            for (int i = 0; i < size; ++i) {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
            capacity *= 2;
        }
        arr[size] = data;
        ++size;
    }

    T& get(int index) {
        return arr[index];
    }

    T get(int index) const {
        return arr[index];
    }

    void set(int index, const T& value) {
        arr[index] = value;
    }

    T* begin() {
        return arr;
    }

    const T* begin() const {
        return arr;
    }
    
    T* end() {
        return arr + size;
    }

    const T* end() const {
        return arr + size;
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    void clear() {
        delete[] arr;
        arr = nullptr;
        capacity = 0;
        size = 0;
        arr = new T[1];
        capacity = 1;
    }
};
