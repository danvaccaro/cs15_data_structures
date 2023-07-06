#ifndef _DATUMSTACK_H_
#define _DATUMSTACK_H_

/*DatumStack.h
  Dan Vaccaro
  2/17/2023

  A DatumStack is a vector-based implementation of a stack ADT. It is intended
  to store Datum objects, which can store either bools, ints, or strings.
  Functionality allows the client to access and manipulate the top element,
  to remove the top element, and to clear the stack. The client can also access
  the size of the stack and check if it is empty.
*/

#include "Datum.h"
#include <vector>

class DatumStack {
public:
    //default constructor
    DatumStack();
    //array constructor
    DatumStack(Datum *inputArray, int size);
    //copy constructor
    DatumStack(const DatumStack &other);
    //assignment operator
    DatumStack operator=(const DatumStack &other);
    //destructor
    ~DatumStack();
    //check if the stack is empty
    bool isEmpty();
    //clear the stack
    void clear();
    //get the size of the stack
    int size();
    //get the top element of the stack
    Datum top();
    //remove the top elemnent of the stack
    void pop();
    //add an element to the top of the stack
    void push(Datum elt);
    //print the stack to the console - debugging only, remove for final program
    void print();
private:
    std::vector<Datum> stack;    
};


#endif