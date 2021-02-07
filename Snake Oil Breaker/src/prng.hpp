//============= ===============================================================
// Name        : prng.hpp
// Author      : Ewa Syta, es633, slightly modified by Michael Fischer
// Description : Fills an array with random values
//============================================================================

#pragma once

#include <iostream>
#include <iomanip>
using namespace std;

#include <cstdlib>

class Prng {
private:
    //Parameters
    unsigned int seed; //Seed used to initialize the prng
    void init();

public:
    Prng (unsigned int s): seed(s) {
        init();
    }
    ~Prng () {}

    void nextBytes(uint8_t buf[], unsigned n); //Fills a buffer with random bytes
    void reset();   //Resets the PRNG
};
