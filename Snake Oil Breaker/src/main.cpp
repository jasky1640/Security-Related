/*
 * main.cpp
 *
 *  Created on: Jan 21, 2012
 *      Author: Michael Fischer
 *      Derived from code by Ewa Syta
 */
#include <ctime>
#include "snakeoil.hpp"

int main(int argc, char* argv[]) {
    try {
        unsigned int seed = time(NULL);
        SnakeOil toplevel(seed);
        toplevel.run(argc, argv);
    }
    catch (exception& e) {
        cerr << "exception caught\n" << e.what() << endl;
    }
    return 0;
}
