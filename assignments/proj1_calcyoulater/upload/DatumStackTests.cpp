/*DatumStackTests.cpp
  Dan Vaccaro
  2/17/2023

  This file runs through some basic tests on the stack functions and
  prints results to the console.
*/

#include "DatumStack.h"
#include <iostream>


int main() {
    std::cout << "Hello world!" << std::endl;
    DatumStack emptyStack;
    emptyStack.print();
    Datum arrayStack[5] = {Datum("a"), Datum("b"), Datum("c"), Datum("d"), Datum("e")};
    DatumStack arrayToStack(arrayStack, 5);
    arrayToStack.print();
    DatumStack copiedStack(arrayToStack);
    copiedStack.print();
    DatumStack assignCopyStack;
    assignCopyStack = copiedStack;
    assignCopyStack.print();
    emptyStack.push(Datum("a"));
    emptyStack.print();
    emptyStack.push(Datum("b"));
    emptyStack.print();
    emptyStack.pop();
    emptyStack.print();
    
    
    return 0;
}