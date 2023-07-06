/*
 *  CharArrayList.h
 *  Dan Vaccaro
 *  01/24/2023
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  CharArrayList is a class representing an expandable list of characters. 
 *  Every instance begins empty and increases in size as characters are
 *  added to the list.
 *  
 *  The client can retrieve values from the list, get the size of the list, 
 *  empty the list, check if the list is empty, convert the data into strings, 
 *  and minimize the memory usage.
 *  
 *  The client has the ability to perform various manipulations on the list.
 *  Primary functions include adding, removing, and replacing characters at 
 *  indexed locations, as well as concatenating lists together.
 * 
 *  Known bugs: valgrind issues messages similar to the one below when
 *  the expand function is called. This does not appear to interfere with the 
 *  class function and no memory leaks are detected.
 *   
 *     Invalid read of size 1
 *         at 0x10C18B: CharArrayList::expand() (CharArrayList.cpp:530)
 * 
 *  Limitations: When running expand() on an exceptionally large list, memory usage 
 *  may momentarily become much than it needs to be. The shrink() function is used
 *  to reclaim the memory after initialization.
 */

#include "CharArrayList.h"

//CharArrayList()
//Parameters: None
//Purpose: Default constructor for CharArrayList. Initializes 
//         an empty array list and sets capacity/size to 0. 
//Return value: N/A
//Other information: N/A
CharArrayList::CharArrayList() {
    data = nullptr;
    num_items = 0;
    capacity = 0;
}

//CharArrayList(char c)
//Parameters: A char to set as the value at index 0. 
//Purpose: One-parameter constructor for CharArrayList. Initializes 
//         an empty array list and sets capacity and size to 1. 
//Return value: N/A
//Other information: N/A
CharArrayList::CharArrayList(char c) {
    capacity = 1;
    num_items = 1;
    data = new char[capacity];
    data[0] = c;
}

//CharArrayList(char arr[], int size)
//Parameters: A char array to copy into the array list and its length.
//Purpose: Two-parameter constructor for CharArrayList. Creates an array list
//         of the same length as the input array and copies the input array
//         values into the new array.
//Return value: N/A
//Other information: This function assumes that the input size is accurate.
//                   If it is smaller than the input array size, the array 
//                   will be copied up to the size. 
CharArrayList::CharArrayList(char arr[], int size) {
    //set the capacity and num_items to the size of the input array
    capacity = size;
    num_items = size;
    //set data to point to a new array with length of size input
    data = new char[capacity];
    //loop through the array and set the value at each
    //index equal to the char at the same index in the input array
    for (int i = 0; i < capacity; ++i) {
        //copy value from input to data array
        data[i] = arr[i];
    }
}

//CharArrayList(const CharArrayList &other)
//Parameters: The address of another array list
//Purpose: Copy constructor for CharArrayList. Creates a deep copy of
//         the input array list.
//Return value: N/A
//Other information: N/A
CharArrayList::CharArrayList(const CharArrayList &other) {
    //set the capacity and num_items to the size of the input list
    capacity = other.capacity;
    num_items = other.num_items;
    //set data to point to a new array with size of other.capacity
    data = new char[capacity];
    //copy data from other into new array
    for (int i = 0; i < capacity; ++i) {
        data[i] = other.data[i];
    }
}

//~CharArrayList()
//Parameters: None
//Purpose: Deconstructor for CharArrayList. Recycles heap memory 
//         associated with the array list.
//Return value: N/A
//Other information: N/A
CharArrayList::~CharArrayList() {
    //deallocate memory for data array
    delete [] data;
    //set data to null pointer
    data = nullptr;
}

//operator=(const CharArrayList &other)
//Parameters: A pointer to a CharArrayList
//Purpose: Creates a deep copy of the input array list
//Return value: A deep copy of the CharArrayList
//Other information: N/A
CharArrayList CharArrayList::operator=(const CharArrayList &other) {
    //check for self-assignment
    if (this == &other) {
        return *this;
    }
    //set capacity and num_items to that of other array list
    capacity = other.capacity;
    num_items = other.num_items;
    //allocate new memory for array copy
    data = new char[capacity];
    //copy data from other into new array
    for (int i = 0; i < capacity; ++i) {
        data[i] = other.data[i];
    }
    //return the new array
    return *this;
}

//isEmpty()
//Parameters: None
//Purpose: Checks whether or not the array list is empty.
//Return value: a bool - true if empty, false otherwise
//Other information: N/A
bool CharArrayList::isEmpty() const {
    if (data == nullptr && capacity == 0) {
        return true;
    }
    else {
        return false;
    }
}

//clear()
//Parameters: None
//Purpose: Turns the current instance into an empty array list.
//Return value: void
//Other information: N/A
void CharArrayList::clear() {
    //recycle heap memory for data
    delete [] data;
    //set data to null pointer
    data = nullptr;
    //set capacity to zero
    capacity = 0;
    //set num_items to zero
    num_items = 0;
}

//size()
//Parameters: None
//Purpose: Gets the current number of elements in the array list
//Return value: An integer representing the size of the list
//Other information: N/A
int CharArrayList::size() const {
    return num_items;
}

//first()
//Parameters: None
//Purpose: Gets the first element of the list if it is not empty.
//Return value: a char representing the first element of the list
//Other information: Throws a runtime exception if the list is empty
char CharArrayList::first() const {
    //check if the list is empty
    if (isEmpty()) {
        //throw a runtime exception
        throw std::runtime_error("cannot get first of empty ArrayList");
    }
    else {
        //return the value at index 0
        return elementAt(0);
    }
}

//last()
//Parameters: None
//Purpose: Gets the last element of the list if it is not empty.
//Return value: a char representing the last element of the list
//Other information: Throws a runtime exception if the list is empty
char CharArrayList::last() const {
    //check if the list is empty
    if (isEmpty()) {
        //throw a runtime exception
        throw std::runtime_error("cannot get last of empty ArrayList");
    }
    else {
        //return the last value in data
        return elementAt(capacity - 1);
    }
}

//elementAt(int index)
//Parameters: The index of the element in the ArrayList
//Purpose: Gets the element at index.
//Return value: The value at index.
//Other information: Throws a range error if the index is out of bounds
char CharArrayList::elementAt(int index) const {
    //check if the list is empty
    if (isEmpty()) {
        //throw a runtime exception
        throw std::runtime_error("cannot get element of empty ArrayList");
    }
    else if (index >= num_items || index < 0) {
         //throw a range exception
        throw std::range_error("index (" + std::to_string(index) + 
                               ") not in range [0.." + 
                               std::to_string(num_items) + ")");
    }
    //otherwise return the value at index
    return data[index];
}

//toString()
//Parameters: None
//Purpose: Generates a message containing the data array and its size
//Return value: String representation of the size and contents of the array
//Other information: N/A
std::string CharArrayList::toString() const {
    //initialize the message with the size
    std::string message = "[CharArrayList of size " + std::to_string(size())
                          + " <<";
    //loop through array and add each char to message
    for (int i = 0; i < capacity; ++i) {
        message += data[i];
    }
    //finish the message
    message += ">>]";
    return message;
}

//toReverseString()
//Parameters: None
//Purpose: Generates a message containing the inverted data array and its size.
//Return value: String representation of the size and the reversed 
//              contents of the array.
//Other information: N/A
std::string CharArrayList::toReverseString() const {
    //initialize the message with the size
    std::string message = "[CharArrayList of size " + std::to_string(capacity) +
                          " <<";
    //loop through array and add each char to message in reverse order
    for (int i = 0; i < capacity; ++i) {
        message += data[capacity - 1 - i];
    }
    //finish the message
    message += ">>]";
    return message;
}

//pushAtBack(char c)
//Parameters: A char to add to the array
//Purpose: Adds a character to the end of the ArrayList
//Return value: None - updates the data in the current instance
//Other information: N/A
void CharArrayList::pushAtBack(char c) {
    //insert at the end of the array
    insertAt(c, size());
}

//pushAtFront(char c)
//Parameters: A char to add to the array
//Purpose: Adds a char to the front of the array
//Return value: None - updates the data in the current instance
//Other information: N/A
void CharArrayList::pushAtFront(char c) {
    //insert at index 0 of the array
    insertAt(c, 0);
}

//insertAt(char c)
//Parameters: A char to add to the array and an int for the index
//Purpose: Adds a char at the given index
//Return value: None - updates the data in the current instance
//Other information: N/A
void CharArrayList::insertAt(char c, int index) {
    //if the array is empty and index is greater than 0
    if (isEmpty() && index > 0) {
        //throw a range exception
        throw std::range_error("index (" + std::to_string(index) + 
                               ") not in range [0.." + 
                               std::to_string(num_items) + "]");
    }
    //check if array is empty and index is correct
    else if (isEmpty()) {
        //increase capacity
        updateCapacity();
        //set num items to 1
        num_items = 1;
        //create a new array of size capacity
        char *new_data = new char[capacity];
        //add to the front of the list
        new_data[0] = c;
        //set data to point to new_data
        recycleAndSetData(new_data);
    }
    //if list is not empty
    else {
        //check that index is in range
        if (index > size() || index < 0) {
            //throw a range exception
            throw std::range_error("index (" + std::to_string(index) + 
                               ") not in range [0.." + 
                               std::to_string(num_items) + "]");
        }
        //increase num_items by 1;
        num_items++;
        //expand list if necessary
        updateCapacity();
        //create a new array with size increased by 1
        char *new_array = new char[size() + 1];
        //copy values from old data to new array, up to index
        for (int i = 0; i < index; i++) {
            new_array[i] = data[i];
        }
        //set value at index equal to c
        new_array[index] = c;
        //loop through the rest of data up to last element
        for(int i = index + 1; i < size(); ++i) {
            new_array[i] = data[i - 1];
        }
        recycleAndSetData(new_array);    
    }
    //shrink to minimize memory usage
    shrink();
}

//insertInOrder(char c)
//Parameters: A char to insert into the array
//Purpose: Insert a character in alphabetical order 
//         relative to the other elements
//Return value: None, updates the current instance
//Other information: This function assumes that the list is already sorted.
//                   If it is not sorted, the char will be inserted before 
//                   the first character that is greater than the input 
//                  (in ASCII value).
void CharArrayList::insertInOrder(char c) {
    //bool to flag whether insertion has occurred
    bool insert_check = false;
    //loop through old array and find index of first character greater than input
    for (int i = 0; i < capacity; ++i) {
        //if the current char in array is less than the input and no insertion
        //has occurred
        if (c < data[i] and !insert_check) {
            //insert the character at the current index
            insertAt(c, i);
            //flag that insertion has occurred
            insert_check = true;
        }
    }
    //if loop completed without finding a place to insert, append to the end
    if(!insert_check) {
        pushAtBack(c);
    }
}

//popFromFront()
//Parameters: None
//Purpose: Removes the first element from the array.
//Return value: None, updates current instance
//Other information: N/A
void CharArrayList::popFromFront(){
    if (isEmpty()) {
        throw std::runtime_error("cannot pop from empty ArrayList");
    }
   //remove the first element from the array
   removeAt(0);
}

//popFromBack()
//Parameters: None
//Purpose: Removes the last element from the array.
//Return value: None, updates current instance
//Other information: N/A
void CharArrayList::popFromBack(){
    if (isEmpty()) {
        throw std::runtime_error("cannot pop from empty ArrayList");
    }
    //remove the last element from the array
    removeAt(size() - 1);
}

//removeAt(int index)
//Parameters: The index in the array at which to remove the element
//Purpose: Removes the element from the specified index.
//Return value: Void, updates the current instance
//Other information: N/A
void CharArrayList::removeAt(int index) {
    //check that index is in range
    if (index >= size() || index < 0) {
        throw std::range_error("index (" + std::to_string(index) + 
                               ") not in range [0.." + 
                               std::to_string(size()) + ")");
    }
    //check if list is one-element
    else if (size() == 1) {
        //empty the list
        clear();
    }
    else {
        //reduce number of items in list by 1
        num_items--;
        //set value at index to -1
        data[index] = -1;
        //create a new array of new size
        char * new_data = new char[size()];
        //a counter for current index in new data
        int new_data_counter = 0;
        //loop through old data
        for (int i = 0; i < capacity; i++) {
            //copy item into new array at position i as long as it isn't -1
            if (data[i] != -1) {
                new_data[new_data_counter] = data[i];
                //increment counter
                new_data_counter++;
            }
        }
        //set data to point to new data
        recycleAndSetData(new_data);
        shrink();
    }
}

//replaceAt(char c, int index)
//Paramters: A char to add to the array and an index at which to add it.
//Purpose: Replaces an element at the given index with the input char
//Return value: Void, updates current instance.
//Other information: N/A
void CharArrayList::replaceAt(char c, int index) {
    if (index >= size() || index < 0) {
        throw std::range_error("index (" + std::to_string(index) + 
                               ") not in range [0.." + 
                               std::to_string(size()) + ")");
    }
    //remove char at index
    removeAt(index);
    //insert char at index
    insertAt(c, index);
}

//concatenate(CharArrayList *other)
//Parameters: An ArrayList to add to the current instance
//Purpose: Appends the input ArrayList data array to the current instance's
//         data array
//Return value: Void, updates current instance
//Other information: N/A
void CharArrayList::concatenate(CharArrayList *other) {
    //if this list is empty, copy everything from the other list
    if (isEmpty()) {
        num_items = other->size();
        capacity = num_items;
        //if there is content in the other list
        if (!other->isEmpty()) {
            //create a new array the same size
            char *new_data = new char[size()];
            //copy the data into the new array
            for (int i = 0; i < size(); i++) {
                new_data[i] = other->elementAt(i);
            }
            recycleAndSetData(new_data);
        }
    }
    //otherwise neither list is empty
    else if(!other->isEmpty()) {
        //expand list until it can fit both arrays
        while (capacity < (size() + other->size())) {
            expand();
        }
        int old_size = size();
        int new_size = old_size + other->size();
        
        //copy values from other into this
        for (int i = old_size; i < new_size; i++) {
            data[i] = other->elementAt(i - old_size);
        }
        //set num_items to new_size;
        num_items = new_size;
        //minimize memory footprint
        shrink();
    }
}

//shrink()
//Parameters: None
//Purpose: Reduces the size of the array to the bare minimum needed to store
//         its elements.
//Return value: None, updates current instance.
//Other information: All ArrayLists in this program are initialized to -1 in all 
//                   slots when they are allocated. This function detects negative
//                   values and removes them from the lists.
void CharArrayList::shrink() {
    if(!isEmpty()) {
        //update new capacity to number of elements
        capacity = size();
        //create new data array of size size()
        char *new_data = new char[size()];
        //a counter to store if an element has been added to new_data
        int data_added_counter = 0;
        //counter to track loops through old array
        int old_array_index = 0;
        //loop through new array until all elements have been added
        while (data_added_counter < size()) {
            //if the value isn't -1
            if (elementAt(old_array_index) != (int)-1) {
                //add the element to the new array
                new_data[data_added_counter] =  elementAt(old_array_index);
                //iterate the counter
                data_added_counter++;
            }
            //iterate old_array_index
            old_array_index++;
        }
        //clean up memory and set data to point to new_data
        recycleAndSetData(new_data);
    } 
}

//expand()
//Parameters: an integer representing the number of slots to add
//            to the list
//Purpose: Expands the list by the given size
//Return value: Void, updates the current instance
//Other information: Expanded slots are initialized to -1
//BUG: This function generates a warning from valgrind (Invalid read of size 1)
//     but there are no other errors/memory leaks affecting program
//     functionality.
void CharArrayList::expand() {
    //set the new capacity to twice the current capacity + 2
    capacity = 2 * capacity + 2;
    //create a new data array with expanded size
    char *new_data = new char[capacity];
    //initialize the new data array with -1
    for (int i = 0; i < capacity; ++i) {
        new_data[i] = -1;
    }
    //fill the new array up to size() with old data
    for (int i = 0; i < size(); ++i) {
        new_data[i] = data[i];
    }
    //clean memory and set data to new array
    recycleAndSetData(new_data);
}

//updateCapacity()
//Parameters: None
//Purpose: Checks if the current list needs to be expanded
//Retrun value: None, updates the current list with an expanded copy
void CharArrayList::updateCapacity(){
    if(size() >= capacity) { 
        expand(); 
    }
}

//recycleAndSetData(char *new_data)
//Parameters: The array with which to replace the old array.
//Purpose: Cleans up memory associated with this instance's data array and
//         updates the data pointer to point to the new array
//Other information: N/A
void CharArrayList::recycleAndSetData(char *new_data) {
    //recycle old data
    delete [] data;
    //set data to point to new array
    data = new_data;
}