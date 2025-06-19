
#pragma once
#include <iostream>

using namespace std;

class ownString {
private:
    char* str;
    int size;
public:
    ownString();
    ownString(const char* string);
    ownString(const ownString& other);
    ownString& operator=(const ownString& other);
    bool operator==(const ownString& other) const;
    bool operator!=(const ownString& other) const;
    ~ownString();
    friend istream& operator>>(istream& input, ownString& string);
    friend ostream& operator<<(ostream& output, ownString& string);
    char operator[](int index) const {
        return str[index];
    }
    int findPos(char letter) const;
    int getLen() const;
    ownString substring(int start, int end) const;
    void removeSpaces() const;
    int convertToInt() const;
    const char* c_str() const;
};
