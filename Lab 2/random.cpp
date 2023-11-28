// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "random.h"

using namespace std;

namespace coen79_lab2
{
    rand_gen::rand_gen(int s, int mul, int inc, int mod) {
        seed = s;
        multiplier = mul;
        increment = inc;
        modulus = mod;
    }
    //     Postcondition: The object has been initialized, and is ready to generate pseudorandom numbers.
    //
    // PUBLIC MODIFICATION member functions for the rand_gen class:
    void rand_gen::set_seed(int newSeed) {
        seed = newSeed;
    }
    //    Postcondition: the number new_seed is the new seed
    int rand_gen::next() {
        int newSeed;
        newSeed = (multiplier * seed + increment) % modulus;
        set_seed(newSeed);
        return newSeed;
    }
    //    Postcondition: The return value is the next random integer, and the return value is set as the new seed
    //
    // PUBLIC CONSTANT member functions for the rand_gen class:
    void rand_gen::print_info() {
        cout << "Seed: " << seed << endl;
        cout << "Multiplier: " << multiplier << endl;
        cout << "Increment: " << increment << endl;
        cout << "Modulus: " << modulus << endl;
    }
}