#pragma once

using namespace std;

template<typename T1, typename T2, typename T3>
class OwnTuple {
private:
    T1 first_;
    T2 second_;
    T3 third_;
public:
    // default constructor
    OwnTuple() {}
    
    // constructor with parameters
    OwnTuple(T1 first, T2 second, T3 third) : first_(first), second_(second), third_(third) {}
    
    // move constructor
    OwnTuple(OwnTuple&& other) : first_(move(other.first_)), second_(move(other.second_)), third_(move(other.third_)) {}
    
    // copy constructor
    OwnTuple(const OwnTuple& other) : first_(other.first_), second_(other.second_), third_(other.third_) {}
    
    // copy assignment operator
    OwnTuple<T1, T2, T3>& operator=(const OwnTuple<T1, T2, T3>& other) { // Copy assignment operator
        if (this != &other) {
            first_ = other.first_;
            second_ = other.second_;
            third_ = other.third_;
        }
        return *this;
    }
    
    // move assignment operator
    OwnTuple& operator=(OwnTuple&& other) { // Move assignment operator
        if (this != &other) {
            first_ = move(other.first_);
            second_ = move(other.second_);
            third_ = move(other.third_);
        }
        return *this;
    }
    T1 getFirst() const {
        return first_;
    }
    void setFirst(T1 first) {
        first_ = first;
    }
    T2 getSecond() const {
        return second_;
    }
    void setSecond(T2 second) {
        second_ = second;
    }
    T3 getThird() const {
        return third_;
    }
    void setThird(T3 third) {
        third_ = third;
    }
    ~OwnTuple() {}
};
