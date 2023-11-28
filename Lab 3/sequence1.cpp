// FILE: sequence1.h
//  Sequence Class
//
//  COEN 79
//
// VALUE SEMANTICS for the sequence class:
//    Assignments and the copy constructor may be used with sequence objects.
//


#include <iostream>
#include <cstdlib>
#include <assert.h>
#include "sequence1.h" 
#include <math.h>

using namespace std;

namespace coen79_lab3 {
    // CONSTRUCTOR for the sequence class:
    sequence::sequence() {
        used = 0;
        start();
    }
    //     Postcondition: The sequence has been initialized as an empty sequence.
    //
    // MODIFICATION MEMBER FUNCTIONS for the sequence class:
    //
    void sequence::start() {
        current_index = 0;
    }
    //      Poscondition: The iterator is reset to position 0;
    //
    void sequence::end() {
        current_index = used;
    }
    //      Poscondition: The iterator points to the last item in the sequence;
    //
    void sequence::last() {
        current_index = CAPACITY - 1;
    }
    //      Poscondition: The iterator is reset to CAPACITY - 1, regardless of the number of items in the sequence;
    //
    void sequence::advance() {
        assert(is_item() == true);
        current_index++;
    }
    //      Precondtion: isitem() returns true
    //      Postcondition: The iterator's value is increased by 1, unless it is already at the end of the sequence.
    //
    void sequence::retreat() {
        assert(current_index > 0);
        if (current_index != 0)
            current_index--;
    }
    //      Postcondition: The iterator's value is reduced by 1, unless it is already at the beginning of the sequence.
    //
    //
    void sequence::insert(const value_type& entry) {
        assert(used < CAPACITY);
        if (used == 0)
            insert_front(entry);
        else {
            for (size_type i = used; i > current_index; i--)
                data[i] = data[i - 1];
            data[current_index] = entry;
            used++;
        }

    }
    //      Precondition: size() < CAPACITY
    //      Postcondition: A new copy of entry has been inserted in the sequence
    //      before the current item. If there was no current item, the new entry
    //      has been inserted at the front. In either case, the new item is now the
    //      current item of the sequence.
    //
    void sequence::attach(const value_type& entry) {
        assert(used < CAPACITY);
        if (used == 0)
            insert_front(entry);
        else {
            current_index++;
            for (size_type i = used; i > current_index; i--)
                data[i] = data[i - 1];
            data[current_index] = entry;
            used++;
        }
    }
    //      Precondition: size() < CAPACITY
    //      Postcondition: A new copy of entry has been inserted in the sequence
    //      after the current item. If there was no current item, the new entry
    //      has been attached to the end. In either case, the new item is now the
    //      current item of the sequence.
    //
    void sequence::remove_current() {
        assert(is_item() == true);
        for (size_type i = current_index; i < used; i++)
            data[i] = data[i + 1];
        used--;

    }
    //      Precondtion: isitem() returns true
    //      Postcondition: The current item has been removed from the sequence,
    //      and the item after this (if there is one) is now the current item.
    //
    //
    void sequence::insert_front(const value_type& entry) {
        assert(used < CAPACITY);
        start();
        for (size_type i = used; i > current_index; i--)
            data[i] = data[i - 1];
        data[current_index] = entry;
        used++;
    }
    //      Precondition: size() < CAPACITY
    //      Postcondition: A new copy of entry has been inserted in the sequence
    //      at the front. The new item is now the current item of the sequence.
    //
    void sequence::attach_back(const value_type& entry) {
        assert(used < CAPACITY);
        end();
        insert(entry);
    }
    //      Precondition: size() < CAPACITY
    //      Postcondition: A new copy of entry has been inserted in the sequence
    //      at the back. The new item is now the current item of the sequence.
    //
    void sequence::remove_front() {
        assert(is_item() == true);
        start();
        for (int i = 0; i < used; i++)
            data[i] = data[i + 1];
        used++;
    }
    //      Precondition: isitem() returns true
    //      Postcondition: The item at the front of the sequence has been removed from the sequence,
    //      and the current item points at the front of the sequence.
    //
    void sequence::operator +=(const sequence& rhs) {
        assert((used + rhs.used) <= CAPACITY);
        for (int i = 0; i < rhs.used; i++)
            attach_back(rhs.data[i]);
    }
    //     Postcondition: Adds the items of rhs to the lhs. Also returns a copy of lhs.
    //
    //
    // CONSTANT MEMBER FUNCTIONS for the sequence class:
    //
    sequence::size_type sequence::size() const {
        return used;
    }
    //      Postcondition: The return value is the number of items in the sequence.
    //
    bool sequence::is_item() const {
        if (current_index < used)
            return true;
        else
            return false;
    }
    //     Postcondition: A true return value indicates that there is a valid
    //     "current" item that may be retrieved by activating the current
    //     member function (listed below). A false return value indicates that
    //     there is no valid current item.
    //
    sequence::value_type sequence::current() const {
        assert(is_item() == true);
        return data[current_index];
    }
    //      Precondtion: isitem() returns true
    //      Poscondition: Returns the item in the sequence at the current position of the iterator.
    //
    sequence::value_type sequence::operator[](int index) const {
        assert(index < used);
        return data[index];
    }
    //     Precondition: index < used
    //     Postcondition: The item returned is the item stored at "index"
    //
    double sequence::mean() const {
        double mean = 0;
        for (int i = 0; i < used; i++)
            mean += data[i];
        return mean / used;

    }
    //     Postcondition: The value returned is the mean of the values stored in the sequence.
    //
    double sequence::standardDeviation() const {
        double sum = 0, sd = 0;
        int i;
        for (i = 0; i < used; ++i)
            sd += pow(data[i] - mean(), 2);
        return sqrt(sd / 10);
    }
    //     Postcondition: The value returned is the stadard deviation of the values stored in the sequence.
    //
    // NON-MEMBER functions for the statistician class:
    //
    sequence operator +(const sequence& lhs, const sequence& rhs) {
        assert((lhs.used + rhs.used) <= lhs.CAPACITY);
        sequence sum(lhs);
        for (int i = 0; i < rhs.used; i++)
            sum.attach_back(rhs.data[i]);
        return sum;
    }
    //     Postcondition: The sequence that is returned contains all the
    //     numbers of the sequences of lsh and rhs.
    //
    //
    sequence::value_type summation(const sequence& s) {
        return s.mean() * s.used;
    }
    //     Postcondition: The value returned is the summation of the values stored in the sequence s.
    //

}



