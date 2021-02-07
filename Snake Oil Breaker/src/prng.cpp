//============================================================================
// Name        : prng.cpp
// Author      : Ewa Syta, es633, slightly modified by Michael Fischer
// Description : Defines prng.hpp
//============================================================================

#include "prng.hpp"

//-----------------------------------------------------------------------
//Initializes the PRNG
void
Prng::init(){
    srand(seed);
}
//-----------------------------------------------------------------------
//Resets the PRNG
void
Prng::reset(){
    srand(seed);
}
//-----------------------------------------------------------------------
//Fills an array with random bytes
void
Prng::nextBytes( uint8_t buf[], unsigned n ){
    for (unsigned i=0; i < n; i++)
    {
            buf[i] = (uint8_t)(rand() % 256);
    }
}
