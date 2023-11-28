#include "node.h"
#include "sequence.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t

using namespace std;

namespace coen79_lab6
{
    // CONSTRUCTOR for the sequence class:
    sequence::sequence() {
        many_nodes = 0;
        head_ptr = NULL;
        tail_ptr = NULL:
        cursor = NULL;
        precursor = NULL;
    }

    sequence(const sequence& source) {
        list_copy(source, head_ptr, tail_ptr);
        many_nodes = source.many_nodes;
        cursor = source.cursor;
        precursor = source.precursor;
    }
    ~sequence() {
        list_clear(head_ptr);
    }

    // MODIFICATION MEMBER FUNCTIONS
    void start() {
        if (head_ptr == NULL)
            return;
        cursor = head_ptr;
    }
    void end() {
        if (head_ptr == NULL)
            return;
        cursor = tail_ptr;
    }
    void advance() {
        assert(is_item() == true);
        if (cursor->link() == NULL) {
            cursor = NULL;
            precursor = tail_ptr;
        }
        else {
            precursor = cursor;
            cursor = cursor->link();
        }
    }
    void insert(const value_type& entry) {
        if (cursor == NULL) {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
        else {
            list_insert(precursor, entry);
            cursor = precursor->link();
        }
    }
    void attach(const value_type& entry) {
        if (cursor == NULL) {
            list_insert(tail_ptr, entry);
            cursor = tail_ptr();
        }
        else {
            list_insert(cursor, entry);
            advance();
        }
    }
    void operator =(const sequence& source) {
        node *first_piece;
        node *second_piece;
        if (source.cursor == NULL) {
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            cursor = NULL;
            precursor = NULL;
        }
        else if (source.cursor == source.head_ptr) {
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            precursor = NULL;
            cursor = head_ptr;
        }
        else {
            precursor = source_precursor;
            cursor = source_cursor;
            list_piece(source.head_ptr, source.precursor, head_ptr, precursor);
            list_piece(source.cursor, source.tail_ptr, cursor, tail_ptr);
            many_nodes = source.many_nodes;

    }
    void remove_current() {
        assert(is_item() == true);
        list_remove(precursor);
    }

    // CONSTANT MEMBER FUNCTIONS
    size_type size() const {
        return many_nodes;
    }
    bool is_item() const {
        if (cursor != NULL)
            return true;
        else
            return false;
    }
    value_type current() const {
        assert(is_item() == true);
        return cursor->data();
    }
    //     Postcondition: The value returned is the summation of the values stored in the sequence s.
    //
}
