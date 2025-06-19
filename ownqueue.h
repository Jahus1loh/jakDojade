#include <iostream>

using namespace std;

template <typename T>
class ownQueue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
    };
    Node* front_;
    Node* end_;
public:
    // default constructor
    ownQueue() : front_(nullptr), end_(nullptr) {}
    
    // copy constructor
    ownQueue(const ownQueue& other) : front_(nullptr), end_(nullptr) {
        Node* currentNode = other.front_;
        while (currentNode != nullptr) {
            push(currentNode->data);
            currentNode = currentNode->next;
        }
    }
    
    // copy assignment operator
    ownQueue& operator=(const ownQueue& other) {
        if (this != &other) {
            ownQueue tmp(other);
            swap(front_, tmp.front_);
            swap(end_, tmp.end_);
        }
        return *this;
    }
    
    // move constructor
    ownQueue(ownQueue&& other) : front_(other.front_), end_(other.end_) {
        other.front_ = nullptr;
        other.end_ = nullptr;
    }
    
    void pop() {
        Node* delNode = front_;
        front_ = front_->next;
        delete delNode;
    }
    
    T front() const {
        return front_->data;
    }
    
    void push(T data) {
        Node* newNode = new Node(data);
        if (empty()) {
            front_ = newNode;
            end_ = newNode;
        } else {
            end_->next = newNode;
            end_ = newNode;
        }
    }
    
    bool empty() {
        return front_ == nullptr;
    }
    
    // deconstructor
    ~ownQueue() {
        while (!empty()) {
            pop();
        }
    }
};

