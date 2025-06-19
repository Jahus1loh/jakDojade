#pragma once

using namespace std;

template<typename T1, typename T2>
class OwnPair {
private:
    T1 first;
    T2 second;
public:
    // default constructor
    OwnPair() {}
    
    // constructor with parameters
    OwnPair(T1 first, T2 second) : first(first), second(second) {}
    
    // deconstructor
    ~OwnPair() {};
    
    // copy constructor
    OwnPair(const OwnPair<T1, T2>& other) : first(other.first), second(other.second) {}
    
    // move constructor
    OwnPair(OwnPair<T1, T2>&& other) noexcept : first(move(other.first)), second(move(other.second)) {
        other.first = T1();
        other.second = T2();
    }
    
    
    OwnPair<T1, T2>& operator=(const OwnPair<T1, T2>& other) {
        if (this != &other) {
            first = other.first;
            second = other.second;
        }
        return *this;
    }
    
    // move assignment operator
    OwnPair<T1, T2>& operator=(OwnPair<T1, T2>&& other) noexcept {
        if (this != &other) {
            first = move(other.first);
            second = move(other.second);
            //other.first_ = T1();
            //other.second_ = T2();
        }
        return *this;
    }
    T1 getFirst() const {
        return first;
    }
    void setFirst(T1 first) {
        this->first = first;
    }
    T2 getSecond() const {
        return second;
    }
    void setSecond(T2 second) {
        this->second = second;
    }
    bool operator==(const OwnPair<T1, T2>& other) const {
        return first == other.first && second == other.second;
    }
    bool operator!=(const OwnPair<T1, T2>& other) const {
        return !(*this == other);
    }
};
