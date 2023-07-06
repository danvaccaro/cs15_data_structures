/*
 * COMP15
 *
 * evil.cpp
 *
 * Driver for lab make lab
 *
 */

#include <iostream>

#include "roster.h"

using namespace std;

/*
 * Evil professor's main functoin to change the student grades!
 */
int main(int argc, char *argv[])
{
        if (argc < 2) {
                cout << "Usage:  ./evil [filename]" << endl;
                return 1;
        }
        Roster r;
        r.do_evil(argv[1]);

        return 0;
}
