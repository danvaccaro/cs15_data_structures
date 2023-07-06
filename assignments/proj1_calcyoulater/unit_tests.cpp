#include "unit_tests.h"
#include "RPNCalc.h"
#include "DatumStack.h"

int main() {
    DatumStack testStack;
    testStack.push(Datum("a"));
    //testStack.print();

    //instantiate an RPNCalc
    RPNCalc testCalc;
    testCalc.run();
    return 0;
}