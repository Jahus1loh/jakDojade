#include <iostream>
#include <stdio.h>
#include "OwnString.hpp"
#include <cmath>

using namespace std;

// default constructor
ownString::ownString() : str(nullptr) {
    str = new char[1];
    str[0] = '\0';
}

//
ownString::ownString(const char* string) {
    int length = 0;
    while (string[length] != '\0') {
        length++;
    }
    str = new char[length + 1];
    for (int i = 0; i < length; i++) {
        str[i] = string[i];
    }
    str[length] = '\0';
    size = length;
}

// copy constructor
ownString::ownString(const ownString& other) {
    if (other.size == 0) {
        size = 1;
        str = new char[1];
        str[0] = '\0';
    } else {
        size = other.size;
        str = new char[other.size + 1];
        for (int i = 0; i < size; i++) {
            str[i] = other.str[i];
        }
        str[size] = '\0';
    }
}

// copy assignment operator
ownString& ownString::operator=(const ownString& other) {
    if (this != &other) {
        delete[] str;
        if (other.str == NULL) {
            str = NULL;
            size = 0;
        } else {
            size = other.size;
            str = new char[size + 1];
            for (int i = 0; i < size; i++) {
                str[i] = other.str[i];
            }
            str[size] = '\0';
        }
    }
    return *this;
    
}

bool ownString::operator==(const ownString& other) const {
    if (str == other.str) {
        return true;
    }
    if (str == NULL || other.str == NULL) {
        return false;
    }
    if (size != other.size) {
        return false;
    }
    for (int i = 0; i < size; i++) {
        if (str[i] != other.str[i]) {
            return false;
        }
    }
    return true;
}

bool ownString::operator!=(const ownString& other) const {
    if (this == NULL) {
        return true;
    }
    if (size != other.size) {
        return true;
    }
    for (int i = 0; i < size; i++) {
        if (str[i] != other.str[i]) {
            return true;
        }
    }
    return false;
}

ownString::~ownString() {
    delete[] str;
}

std::istream& operator>>(std::istream& input, ownString& str) {
    char* buffer = new char[1024];
    input.getline(buffer, 1024);
    str = ownString(buffer);
    delete[] buffer;
    return input;
}

ostream& operator<<(ostream& output, ownString& string) {
    output << string.str;
    return output;
}

int ownString::getLen() const {
    return size;
}

int ownString::findPos(char letter) const {
    for (int i = 0; i < size; i++) {
        if (str[i] == letter) {
            return i;
        }
    }
    return -1;
}

// return substring from start to end pos of givens string
ownString ownString::substring(int start, int end) const {
    // check if the start index is within the string
    if (start < 0 || start >= size || end < start || end > size) {
        return ownString();
    }
    char* buffer = new char[end - start + 1];
    for (int i = start; i < end; i++) {
        buffer[i - start] = str[i];
    }
    buffer[end - start] = '\0';
    ownString result(buffer);
    delete[] buffer;
    return result;
}

int ownString::convertToInt() const {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result = result * 10 + (str[i]- '0');
    }
    return result;
}

void ownString::removeSpaces() const {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ') {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

const char* ownString::c_str() const {
    if (str == nullptr) {
        return "";
    } else {
        return str;
    }
}
