// FILE: node.cpp
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
        // Library facilities used: cstdlib
    {
        const node* cursor;
        size_t answer;

        answer = 0;
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
            ++answer;

        return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
        head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
        node* insert_ptr;

        insert_ptr = new node(entry, previous_ptr->link());
        previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
        // Library facilities used: cstdlib
    {
        node* cursor;

        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
            if (target == cursor->data())
                return cursor;

        return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
        // Library facilities used: cstdlib
    {
        const node* cursor;

        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
            if (target == cursor->data())
                return cursor;

        return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
        // Library facilities used: cassert, cstdlib
    {
        node* cursor;
        size_t i;

        assert(0 < position);
        cursor = head_ptr;
        for (i = 1; (i < position) && (cursor != NULL); i++)
            cursor = cursor->link();

        return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
        // Library facilities used: cassert, cstdlib
    {
        const node* cursor;
        size_t i;

        assert(0 < position);
        cursor = head_ptr;
        for (i = 1; (i < position) && (cursor != NULL); i++)
            cursor = cursor->link();

        return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
        node* remove_ptr;

        remove_ptr = head_ptr;
        head_ptr = head_ptr->link();
        delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
        node* remove_ptr;

        remove_ptr = previous_ptr->link();
        previous_ptr->set_link(remove_ptr->link());
        delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
        // Library facilities used: cstdlib
    {
        while (head_ptr != NULL)
            list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
        // Library facilities used: cstdlib
    {
        head_ptr = NULL;
        tail_ptr = NULL;

        // Handle the case of the empty list.
        if (source_ptr == NULL)
            return;

        // Make the head node for the newly created list, and put data in it.
        list_head_insert(head_ptr, source_ptr->data());
        tail_ptr = head_ptr;

        // Copy the rest of the nodes one at a time, adding at the tail of new list.
        source_ptr = source_ptr->link();
        while (source_ptr != NULL)
        {
            list_insert(tail_ptr, source_ptr->data());
            tail_ptr = tail_ptr->link();
            source_ptr = source_ptr->link();
        }
    }
    // ------------------------------
    void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr) {
        head_ptr = NULL;
        tail_ptr = NULL;
        if (start_ptr == NULL)
            return;
        list_head_insert(head_ptr, start_ptr->data());
        //        head_ptr->set_link(tail_ptr);
        tail_ptr = head_ptr;
        start_ptr = start_ptr->link();
        while (start_ptr != end_ptr) {
            list_insert(tail_ptr, start_ptr->data());
            tail_ptr = tail_ptr->link();
            start_ptr = start_ptr->link();
        }
        //      }
    }
    size_t list_occurrences(node* head_ptr, const node::value_type& target) {
        node* cursor;
        size_t count = 0;
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link()) {
            if (cursor->data() == target)
                count++;
        }
        return count;
    }
    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position) {
        node* cursor;
        size_t i;
        assert((position > 0) && (position <= list_length(head_ptr) + 1));
        cursor = head_ptr;
        if (position == 1)
            list_head_insert(head_ptr, entry);
        else {
            for (i = 1; (i < position) && (cursor != NULL); i++)
                cursor = cursor->link();
            list_insert(cursor, entry);
        }
    }
    node::value_type list_remove_at(node*& head_ptr, size_t position) {
        node* cursor;
        node::value_type data;
        size_t i;
        assert((position > 0) && (position <= list_length(head_ptr)));
        cursor = head_ptr;
        if (position == 1) {
            list_head_remove(head_ptr);
            return cursor->data();
        }
        else {
            for (i = 1; (i < position) && (cursor != NULL); i++)
                cursor = cursor->link();
            data = cursor->data();
            list_remove(cursor);
            return data;
        }
    }


    node* list_copy_segment(node* head_ptr, size_t start, size_t finish) {
        node* cursor;
        node* newhead_ptr;
        size_t i;
        assert((1 <= start) && (start <= finish) && (finish <= list_length(head_ptr)));
        newhead_ptr = list_locate(head_ptr, start);
        newhead_ptr->set_link(cursor);
        for (i = start + 1; i < finish; i++) {
            cursor = list_locate(head_ptr, i);
        }
        return newhead_ptr;
    }
    void list_print(const node* head_ptr) {
        const node* cursor;
        node::value_type data;
        for (cursor = head_ptr; (cursor != NULL) && (cursor->link() != NULL); cursor = cursor->link()) {
            data = cursor->data();
            cout << data << ", ";
        }
        data = cursor->data();
        cout << data << endl;
    }

    void list_remove_dups(node* head_ptr) {
        node* cursor;
        cursor = head_ptr;
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link()) {
            if (cursor->data() == head_ptr->data())
                list_remove(cursor);
        }
    }
    node* list_detect_loop(node* head_ptr) {
        node* slow;
        node* fast;
        while (slow != NULL && fast != NULL && fast->link() != NULL) {
            slow = slow->link();
            fast = fast->link();
            if (slow == fast)
                return slow;
        }
        return NULL;

    }

}
