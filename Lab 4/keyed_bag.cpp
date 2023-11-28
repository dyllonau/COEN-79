#include <cstdlib>  // Provides size_t
#include <string>
#include <assert.h>
#include <algorithm>
#include "keyed_bag.h"

using namespace std;

namespace coen79_lab4 {
    // CONSTRUCTOR for the keyed_bag class:
    keyed_bag::keyed_bag() {
        bag_count = 0;
    }
    //     Postcondition: The keyed_bag has been initialized as an empty keyed_bag.
    //
    //
    // MODIFICATION MEMBER FUNCTIONS for the keyed_bag class:
    void keyed_bag::erase() {
        key_type newkeys[CAPACITY];
        value_type newdata[CAPACITY];
        copy(newkeys, newkeys + CAPACITY, keys);
        copy(newdata, newdata + CAPACITY, data);
        bag_count = 0;
    }
    //     Postcondition: This keyed_bag is emptied of all items and keys.
    //
    bool keyed_bag::erase(const key_type& key) {
        for (size_type i = 0; i < bag_count; i++) {
            if (keys[i] == key) {
                keys[i] = keys[bag_count - 1];
                data[i] = data[bag_count - 1];
                bag_count--;
                return true;
            }
        }
        return false;
    }
    //     Postcondition: If key was in the keyed_bag, then the key and its value have been removed;
    //     otherwise the keyed_bag is unchanged. A true return value indicates that an
    //     item was removed; false indicates that nothing was removed.
    //
    void keyed_bag::insert(const value_type& entry, const key_type& key) {
        assert(size() < CAPACITY);
        assert(has_key(key) == false);
        data[bag_count] = entry;
        keys[bag_count] = key;
        bag_count++;
    }
    //     Precondition:  size( ) < CAPACITY, and the keyed_bag does not yet contain
    //     the given key.
    //     Postcondition: A new copy of entry has been added to the keyed_bag with
    //     the corresponding key.
    //
    void keyed_bag::operator +=(const keyed_bag& addend) {
        assert(size() + addend.size() <= CAPACITY);
        assert(hasDuplicateKey(addend) == false);
        copy(addend.keys, addend.keys + addend.bag_count, keys + bag_count);
        copy(addend.data, addend.data + addend.bag_count, data + bag_count);
        bag_count += addend.bag_count;
    }
    //     Precondition:  size( ) + addend.size( ) <= CAPACITY.
    //     The intersection of the keyed_bags' key tables is empty (i.e. the keyed_bags)
    //     share no keys.
    //     Postcondition: Each item and its key in addend has been added to this keyed_bag.
    //
    //
    // CONSTANT MEMBER FUNCTIONS for the keyed_bag class:
    bool keyed_bag::has_key(const key_type& key) const {
        for (size_type i = 0; i < bag_count; i++) {
            if (keys[i] == key)
                return true;
        }
        return false;
    }
    //     Postcondition: The return value is whether or not the given key is in
    //     the keyed_bag's list of keys.
    //
    keyed_bag::value_type keyed_bag::get(const key_type& key) const {
        assert(has_key(key) == true);
        int index = 0;
        for (size_type i = 0; i < bag_count; i++) {
            if (keys[i] == key) {
                index = i;
                break;
            }
        }
        return data[index];
    }
    //     Precondition: has_key returns true for the given key.
    //     Postcondition: the data value corresponding to the given key is returned.
    //
    keyed_bag::size_type keyed_bag::size() const {
        return bag_count;
    }
    //     Postcondition: The return value is the total number of items in the keyed_bag.
    //
    keyed_bag::size_type keyed_bag::count(const value_type& target) const {
        size_type count = 0;
        for (size_type i = 0; i < bag_count; i++) {
            if (data[i] == target)
                count++;
        }
        return count;
    }
    //     Postcondition: The return value is number of times target is in the keyed_bag.
    //
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const {
        for (size_type i = 0; i < bag_count; i++) {
            if (keys[i] == otherBag.keys[i])
                return true;
        }
        return false;
    }
    //     Postcondition: The return value is true if there is at least one key used by both this bag and the "otherBag". In other words, this function checks if there is any shared key by the two bags.
    //

    // NONMEMBER FUNCTIONS for the keyed_bag class
    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2) {
        assert(b1.size() + b2.size() <= keyed_bag::CAPACITY);
        assert(b1.hasDuplicateKey(b2) == false);
        keyed_bag newbag;
        newbag += b1;
        newbag += b2;
        return newbag;
    }
    //     Precondition:  b1.size( ) + b2.size( ) <= keyed_bag::CAPACITY.
    //                    The intersection of the keyed_bags' key tables is empty.
    //                    (i.e. The two keyed_bag's have no keys in common.)
    //     Postcondition: The keyed_bag returned is the union of b1 and b2.
    //}
    //
}