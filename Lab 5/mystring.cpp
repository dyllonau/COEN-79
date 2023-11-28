#include <cstdlib>  // Provides size_t
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <assert.h>
#include "mystring.h"

using namespace std;
using namespace coen79_lab5;

namespace coen79_lab5 {
    // CONSTRUCTOR, COPY CONSTRUCTOR, and DESTRUCTOR
    string::string(const char str[]) {
        current_length = 0;
        characters = NULL;
        reserve(strlen(str));
        if (characters != NULL) {
            for (size_t i = 0; i < strlen(str); i++) {
                characters[i] = str[i];
                current_length++;
            }
        }
    }
    string::string(char c) {                     // NEW FUNCTION 1
        *characters = c;
        reserve(10);
    }
    string::string(const string& source) {
        characters = new char[source.length()];
        current_length = source.length();
        allocated = source.allocated;
        copy(source.characters, source.characters + source.length(), characters);
    }
    string::~string() {
        delete[] characters;
    }

    // MODIFICATION MEMBER FUNCTIONS
    void string::operator +=(const string& addend) {
        strcat(characters, addend.characters);
        current_length += addend.current_length;
    }
    void string::operator +=(const char addend[]) {
        strcat(characters, addend);
        current_length += strlen(addend);
    }
    void string::operator +=(char addend) {
        characters[current_length] = addend;
        current_length++;
    }
    void string::reserve(size_t n) {
        char* more = new char[n];
        if (characters != NULL) {
            copy(characters, characters + current_length, more);
            delete[] characters;
            characters = more;
        }
        else
            characters = more;
        allocated = n;
    }

    string& string::operator =(const string& source) {
        char* newstring = new char[source.length()];
        copy(source.characters, source.characters + source.current_length, newstring);
        current_length = source.current_length;
        delete[] characters;
        characters = newstring;
        return *this;
    }
    void string::insert(const string& source, unsigned int position) {
        assert(position <= current_length);
        if (current_length + source.length() > allocated);
        reserve(current_length + source.length() + 10);
        char store[current_length];
        size_t j = 0;
        for (size_t i = position; i < current_length; i++)
            store[j++] = characters[i];
        size_t k = 0;
        for (size_t i = position; i < position + source.length(); i++) {
            characters[i] = source[k++];
        }
        size_t og = current_length;
        size_t l = 0;
        current_length += source.length();
        for (size_t i = position; i < og; i++) {
            characters[++k] = store[l++];
        }
    }
    void string::dlt(unsigned int position, unsigned int num) {
        assert((position + num) <= length());
        char stored[current_length - num];
        copy(characters, characters + position - 1, stored);
        copy(characters + position + num, characters + length(), stored + position - 1);
        delete[] characters;
        copy(stored, stored + current_length - num, characters);
        current_length -= num;
    }
    void string::replace(char c, unsigned int position) {
        assert(position < length());
        characters[position] = c;
    }
    void string::replace(const string& source, unsigned int position) {
        assert((position + source.length()) <= length());
        int index = 0;
        for (unsigned int i = position; i < position + source.length(); i++) {
            characters[i] = source[index++];
        }
    }
    // CONSTANT MEMBER FUNCTIONS
    char string::operator [ ](size_t position) const {
        assert(position < length());
        return characters[position];
    }
    int string::search(char c) const {
        int count = 0;
        for (int i = 0; i < length(); i++) {
            if (characters[i] == c)
                return i;
        }
        return -1;
    }

    int string::search(const string& substring) const {
        if (strstr(characters, substring.characters) != NULL) {
            for (size_t i = 0; i < length(); i) {
                if (characters[i] == substring[0])
                    return i;
            }
        }
        else
            return -1;
    }
    unsigned int string::count(char c) const {
        int count = 0;
        count = std::count(characters, characters + length(), c);
        return (unsigned int)count;
    }

    // FRIEND FUNCTIONS
    std::ostream& operator <<(std::ostream& outs, const string& source) {
        for (size_t i = 0; i < source.length(); i++)
            outs << source.characters[i];
        return outs;
    }
    bool operator ==(const string& s1, const string& s2) {
        if (strcmp(s1.characters, s2.characters) == 0)
            return true;
        else
            return false;
    }
    bool operator !=(const string& s1, const string& s2) {
        if (strcmp(s1.characters, s2.characters) == 0)
            return false;
        else
            return true;
    }
    bool operator > (const string& s1, const string& s2) {
        if (strcmp(s1.characters, s2.characters) > 0)
            return true;
        else
            return false;
    }
    bool operator < (const string& s1, const string& s2) {
        if (strcmp(s1.characters, s2.characters) < 0)
            return true;
        else
            return false;
    }
    bool operator >=(const string& s1, const string& s2) {
        if (strcmp(s1.characters, s2.characters) >= 0)
            return true;
        else
            return false;
    }
    bool operator <=(const string& s1, const string& s2) {
        if (strcmp(s1.characters, s2.characters) <= 0)
            return true;
        else
            return false;
    }


    string operator +(const string& s1, const string& s2) {
        string s = s1;
        s += s2;
        return s;
    }
    string operator +(const string& s1, const char addend[]) {
        string s = s1;
        s += addend;
        return s;
    }
    std::istream& operator >> (std::istream& ins, string& target) {
        char c;
        char source[50];
        ins >> source;
        target = source;
        return ins;
    }
}
