#pragma once

#include <iostream>
#include "OwnVector.h"
#include "OwnPair.h"
#include "OwnString.hpp"
#include <functional>

using namespace std;

template<typename keyT, typename valueT>
class ownUnorderedMap {
private:
    struct Node {
        keyT key;
        valueT value;
        bool occupied;
        Node() : occupied(false) {}
    };
    Node* table;
    size_t numbOfBuckets;
    size_t numbOfElements;
    size_t ownHasher(const ownString& str) {
        const char* s = str.c_str();
        size_t hash = 5381;
        int c;
        
        while ((c = *s++)) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash;
    }
    void resize(size_t newSize) {
        Node* newTable = new Node[newSize];
        for (size_t i = 0; i < newSize; i++) {
            newTable[i].occupied = false;
        }
        for (size_t i = 0; i < numbOfBuckets; i++) {
            if (table[i].occupied) {
                size_t hash_value = ownHasher(table[i].key);
                size_t index = hash_value % newSize;
                
                while (newTable[index].occupied) {
                    index = (index + 1) % newSize;
                }
                
                newTable[index].key = table[i].key;
                newTable[index].value = table[i].value;
                newTable[index].occupied = true;
            }
        }
        if (table != nullptr) {
            delete[] table;
        }
        table = newTable;
        numbOfBuckets = newSize;
    }
public:
    // default constructor
    ownUnorderedMap() : table(nullptr), numbOfBuckets(0), numbOfElements(0) {}
    
    // copy constructor
    ownUnorderedMap(const ownUnorderedMap& other) : table(nullptr), numbOfBuckets(0), numbOfElements(0) {
        if (other.numbOfBuckets == 0) {
            return;
        }
        resize(other.numbOfBuckets);
        for (size_t i = 0; i < other.numbOfBuckets; i++) {
            if (other.table[i].occupied) {
                push(other.table[i].key, other.table[i].value);
            }
        }
    }
    
    // move constructor
    ownUnorderedMap(ownUnorderedMap&& other) : table(other.table), numbOfBuckets(other.numbOfBuckets), numbOfElements(other.numbOfElements) {
        other.table = nullptr;
        other.numbOfBuckets = 0;
        other.numbOfElements = 0;
    }
    
    // copy assignment opeator
    ownUnorderedMap& operator=(const ownUnorderedMap& other) {
        if (this != &other) {
            ownUnorderedMap temp(other);
            swap(table, temp.table);
            swap(numbOfBuckets, temp.numbOfBuckets);
            swap(numbOfElements, temp.numbOfElements);
        }
        return *this;
    }

    // move assignment operator
    ownUnorderedMap& operator=(ownUnorderedMap&& other) {
        if (this != &other) {
            if (table != nullptr) {
                delete[] table;
            }
            table = move(other.table);
            numbOfBuckets = move(other.numbOfBuckets);
            numbOfElements = move(other.numbOfElements);
            //other.table = nullptr;
            //other.numbOfBuckets = 0;
            //other.numbOfElements = 0;
        }
        return *this;
    }

    // add value at the end of the map
    void push(const keyT& key, const valueT& value) {
        // if number of buckets is equal to 0, resize the map
        if (numbOfBuckets == 0) {
            resize(8);
        }
        // calculate hash value and index
        size_t hashVal = ownHasher(key);
        size_t index = hashVal % numbOfBuckets;

        while (table[index].occupied) {
            // if there exist already the data with this key change it to new value
            if (table[index].key == key) {
                table[index].value = value;
                return;
            }
            index = (index + 1) % numbOfBuckets;
        }
        table[index].key = key;
        table[index].value = value;
        table[index].occupied = true;
        numbOfElements++;
        if (2 * numbOfElements >= numbOfBuckets) {
            resize(2 * numbOfBuckets);
        }
    }
    
    // return value which is assigned to the key
    valueT& operator[](const keyT& key) {
        if (numbOfBuckets == 0) {
            resize(8);
        }
        size_t hashVal = ownHasher(key);
        size_t index = hashVal % numbOfBuckets;

        while (table[index].occupied) {
            if (table[index].key == key) {
                return table[index].value;
            }
            index = (index + 1) % numbOfBuckets;
        }
        table[index].key = key;
        table[index].value = valueT();
        table[index].occupied = true;
        numbOfElements++;
        if (2 * numbOfElements >= numbOfBuckets) {
            resize(2 * numbOfBuckets);
        }
        return table[index].value;
    }
    
    // count number of occurences of key
    int count(keyT key) {
        int count = 0;
        if (numbOfBuckets == 0) {
            return 0;
        }
        size_t hashVal = ownHasher(key);
        size_t index = hashVal % numbOfBuckets;

        while (table[index].occupied) {
            if (table[index].key == key) {
                count++;
            }
            index = (index + 1) % numbOfBuckets;
        }
        return count;
    }
    
    // search the key by its value
    keyT searchByValue(const ownUnorderedMap<keyT, valueT>& map, const valueT& value) {
        for (size_t i = 0; i < map.numbOfBuckets; i++) {
            if (map.table[i].occupied && map.table[i].value == value) {
                return map.table[i].key;
            }
        }
        throw std::out_of_range("Out of range");
    }
    
    int getSize() const {
        return this->numbOfElements;
    }
    
    // deconstructor
    ~ownUnorderedMap() {
        if (table != nullptr) {
            delete[] table;
        }
    }
};
