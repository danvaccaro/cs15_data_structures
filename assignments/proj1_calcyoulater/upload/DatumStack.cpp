/*DatumStack.cpp
  Dan Vaccaro
  2/17/2023

  A DatumStack is a vector-based implementation of a stack ADT. It is intended
  to store Datum objects, which can store either bools, ints, or strings.
  Functionality allows the client to access and manipulate the top element,
  to remove the top element, and to clear the stack. The client can also access
  the size of the stack and check if it is empty.
*/
#include "DatumStack.h"
#include <iostream>
#include <stdexcept>

/*DatumStack
  Purpose: Default constructor - does nothing.*/
DatumStack::DatumStack() {}

/*DatumStack(Datum *inputArray, int size)
  Purpose: 2 parameter constructor. Reads the contents of a Datum array
           into a stack.
  Parameters: A pointer to a Datum array and the size of the array.
*/
DatumStack::DatumStack(Datum *inputArray, int size) {
    //push values from array to top of stack
    for (int i = 0; i < size; ++i)
        stack.push_back(inputArray[i]);
}
 /*DatumStack(const DatumStack &other)
   Purpose: Copy constructor - creates a deep copy of the input stack.*/
DatumStack::DatumStack(const DatumStack &other) {
    //instantiate a new stack vector
    std::vector<Datum> newStack;
    //loop through other stack
    for (uint i = 0; i < other.stack.size(); ++i)
        //push the value at the index to the top of the new stack
        newStack.push_back(other.stack[i]);
    //set stack to the copied vector
    stack = newStack;
}
/*operator=(const DatumStack &other)
  Purpose: Assignment operator - creates a deep copy of the input stack and
           assigns it to the caller's stack.
  Parameters: A DatumStack to copy.*/
DatumStack DatumStack::operator=(const DatumStack &other) {
    //if other is the same as this, return this
    if (this == &other)
        return *this;
    //instantiate a new stack vector
    std::vector<Datum> newStack;
    //loop through other stack
    for (uint i = 0; i < other.stack.size(); ++i)
        //push the value at the index to the top of the new stack
        newStack.push_back(other.stack[i]);
    //set stack to the copied vector
    stack = newStack;
    //return a pointer to the updated stack
    return *this;
}

/*~DatumStack()
  Purpose: Destructor - clears the stack before deleting.*/
DatumStack::~DatumStack() {
    stack.clear();
}

/*isEmpty
  Purpose: Checks if the current stack is empty.
  ParametersL None.
  Return value: A bool - true if empty, false otherwise*/
bool DatumStack::isEmpty() {
    //check if the stack vector is empty
    return stack.empty();
}
/*clear()
  Purpose: Empties the stack.
  Parameters: None
  Return value: Void, updates the current instance.*/
void DatumStack::clear() {
    //clear the stack vector
    stack.clear();
}
/*size()
  Purpose: Retrieves the number of elements in the stack.
  Parameters: None.
  Return value: A int representing the size of the stack.*/
int DatumStack::size() {
    //return the size of the stack vector
    return stack.size();
}
/*top()
  Purpose: Gets the value at the top of the stack (does not remove).
  Parameters: None.
  Return value: The Datum on the top of the stack.*/
Datum DatumStack::top() {
    //if the stack vector is empty throw an exception
    if (isEmpty())
        throw std::runtime_error("empty_stack");
    //else return the value at the back of the stack
    return stack.back();
}
/*pop()
  Purpose: Removes the element at the top of the stack.
  Parameters: None.
  Return value: Void, updates the current instance.*/
void DatumStack::pop() {
    //if the stack vector is empty throw an exception
    if (isEmpty())
        throw std::runtime_error("empty_stack");
    //else pop the last element in the vector
    stack.pop_back();
}
/*push()
  Purpose: Pushes a Datum to the top of the stack.
  Parameters: A Datum to push.
  Return value: None, updates the current instance.*/
void DatumStack::push(Datum elt) {
    //push the input to the back of the stack vector
    stack.push_back(elt);
}
 /*print()
   Purpose: Prints the stack to the console.
   DEBUGGING PURPOSES ONLY*/
void DatumStack::print() {
  std::cout << std::endl;
    std::cout << "TOP" << std::endl;
    for (int i = size() - 1; i >= 0; --i)
        std::cout << stack[i].toString() << std::endl;
    std::cout << "BOTTOM\n\n";
}