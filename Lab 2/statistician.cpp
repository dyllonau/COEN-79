// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician.h"

using namespace std;

namespace coen79_lab2
{
    // CONSTRUCTOR for the statistician class:
    statistician::statistician() {
        total = 0;
        size = 0;
        min = 0;
        max = 0;
        avg = 0;
    }
    //     Postcondition: The object has been initialized, and is ready to accept
    //     a sequence of numbers. Various statistics will be calculated about the
    //     sequence.
    //
    // PUBLIC MODIFICATION member functions for the statistician class:
    void statistician::next(double r) {
        total += r;
        if (r < min || size == 0)
            min = r;
        if (r > max || size == 0)
            max = r;
        size++;
        avg = total / size;
    }
    //     The number r has been given to the statistician as the next number in
    //     its sequence of numbers.
    void statistician::reset() {
        total = 0;
        size = 0;
        min = 0;
        max = 0;
        avg = 0;
    }
    //     Postcondition: The statistician has been cleared, as if no numbers had
    //     yet been given to it.
    //   
    // PUBLIC CONSTANT member functions for the statistician class:
    int statistician::length() const {
        return size;
    }
    //     Postcondition: The return value is the length of the sequence that has
    //     been given to the statistician (i.e., the number of times that the
    //     next(r) function has been activated).
    double statistician::sum() const {
        return total;
    }
    //     Postcondition: The return value is the sum of all the numbers in the
    //     statistician's sequence.
    double statistician::mean() const {
        return avg;
    }
    //     Precondition: length( ) > 0
    //     Postcondition: The return value is the arithmetic mean (i.e., the
    //     average of all the numbers in the statistician's sequence).
    double statistician::minimum() const {
        return min;
    }
    //     Precondition: length( ) > 0
    //     Postcondition: The return value is the tiniest number in the
    //     statistician's sequence.
    double statistician::maximum() const {
        return max;
    }
    //     Precondition: length( ) > 0
    //     Postcondition: The return value is the largest number in the
    //     statistician's sequence.
    //
    // NON-MEMBER functions for the statistician class:
    statistician operator +(const statistician& s1, const statistician& s2) {
        statistician sum;
        sum.total = s1.total + s2.total;
        sum.size = s1.size + s2.size;
        if (s1.min <= s2.min)
            sum.min = s1.min;
        else
            sum.min = s2.min;
        if (s1.max >= s2.max)
            sum.max = s1.max;
        else
            sum.max = s2.max;
        sum.avg = sum.total / sum.size;
        return sum;
    }
    //     Postcondition: The statistician that is returned contains all the
    //     numbers of the sequences of s1 and s2.
    statistician operator *(double scale, const statistician& s) {
        statistician product;
        product.total = s.total * scale;
        product.avg = product.total / s.size;
        product.min = s.max * scale;
        product.max = s.min * scale;
        return product;
    }
    //     Postcondition: The statistician that is returned contains the same
    //     numbers that s does, but each number has been multiplied by the
    //     scale number.
    bool operator ==(const statistician& s1, const statistician& s2) {
        if (s1.size == s2.size == 0 || (s1.size == s2.size &&
            s1.avg == s2.avg && s1.min == s2.min && s1.max == s2.max &&
            s1.total == s2.total))
            return true;
        else
            return false;
    }
    //     Postcondition: The return value is true if s1 and s2 have the zero
    //     length. Also, if the length is greater than zero, then s1 and s2 must
    //     have the same length, the same  mean, the same minimum, 
    //     the same maximum, and the same sum.


}

