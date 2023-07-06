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

#ifndef CHAR_ARRAY_LIST_H
#define CHAR_ARRAY_LIST_H

#include <string>
#include <iostream>
#include <stdexcept>

class CharArrayList {
public: 
//CharArrayList()
//Parameters: None
//Purpose: Default constructor for CharArrayList. Initializes 
//         an empty array list and sets capacity/size to 0. 
//Return value: N/A
//Other information: N/A
    CharArrayList();
    
//CharArrayList(char c)
//Parameters: A char to set as the value at index 0. 
//Purpose: One-parameter constructor for CharArrayList. Initializes 
//         an empty array list and sets capacity and size to 1. 
//Return value: N/A
//Other information: N/A
    CharArrayList(char c);

//CharArrayList(char arr[], int size)
//Parameters: A char array to copy into the array list and its length.
//Purpose: Two-parameter constructor for CharArrayList. Creates an array list
//         of the same length as the input array and copies the input array
//         values into the new array.
//Return value: N/A
//Other information: This function assumes that the input size is accurate.
//                   If it is smaller than the input array size, the array 
//                   will be copied up to the size.    
    CharArrayList(char arr[], int size);

//CharArrayList(const CharArrayList &other)
//Parameters: The address of another array list
//Purpose: Copy constructor for CharArrayList. Creates a deep copy of
//         the input array list.
//Return value: N/A
//Other information: N/A
    CharArrayList(const CharArrayList &other);

//~CharArrayList()
//Parameters: None
//Purpose: Deconstructor for CharArrayList. Recycles heap memory 
//         associated with the array list.
//Return value: N/A
//Other information: N/A
    ~CharArrayList();

//operator=(const CharArrayList &other)
//Parameters: A pointer to a CharArrayList
//Purpose: Creates a deep copy of the input array list
//Return value: A deep copy of the CharArrayList
//Other information: N/A
    CharArrayList operator=(const CharArrayList &other);

//isEmpty()
//Parameters: None
//Purpose: Checks whether or not the array list is empty.
//Return value: a bool - true if empty, false otherwise
//Other information: N/A
    bool isEmpty() const;

//clear()
//Parameters: None
//Purpose: Turns the current instance into an empty array list.
//Return value: void
//Other information: N/A
    void clear();

//size()
//Parameters: None
//Purpose: Gets the current number of elements in the array list
//Return value: An integer representing the size of the list
//Other information: N/A
    int size() const;

//first()
//Parameters: None
//Purpose: Gets the first element of the list if it is not empty.
//Return value: a char representing the first element of the list
//Other information: Throws a runtime exception if the list is empty
    char first() const;

//last()
//Parameters: None
//Purpose: Gets the last element of the list if it is not empty.
//Return value: a char representing the last element of the list
//Other information: Throws a runtime exception if the list is empty
    char last() const;

//elementAt(int index)
//Parameters: The index of the element in the ArrayList
//Purpose: Gets the element at index.
//Return value: The value at index.
//Other information: Throws a range error if the index is out of bounds
    char elementAt(int index) const;

//toString()
//Parameters: None
//Purpose: Generates a message containing the data array and its size
//Return value: String representation of the size and contents of the array
//Other information: N/A
    std::string toString() const;

//toReverseString()
//Parameters: None
//Purpose: Generates a message containing the inverted data array and its size.
//Return value: String representation of the size and the reversed 
//              contents of the array.
//Other information: N/A
    std::string toReverseString() const;

//pushAtBack(char c)
//Parameters: A char to add to the array
//Purpose: Adds a character to the end of the ArrayList
//Return value: None - updates the data in the current instance
//Other information: N/A   
    void pushAtBack(char c);

//pushAtFront(char c)
//Parameters: A char to add to the array
//Purpose: Adds a char to the front of the array
//Return value: None - updates the data in the current instance
//Other information: N/A
    void pushAtFront(char c);

//insertAt(char c)
//Parameters: A char to add to the array and an int for the index
//Purpose: Adds a char at the given index
//Return value: None - updates the data in the current instance
//Other information: N/A
    void insertAt(char c, int index);

//insertInOrder(char c)
//Parameters: A char to insert into the array
//Purpose: Insert a character in alphabetical order 
//         relative to the other elements
//Return value: None, updates the current instance
//Other information: This function assumes that the list is already sorted.
//                   If it is not sorted, the char will be inserted before 
//                   the first character that is greater than the input 
//                  (in ASCII value).
    void insertInOrder(char c);

//popFromFront()
//Parameters: None
//Purpose: Removes the first element from the array.
//Return value: None, updates current instance
//Other information: N/A
    void popFromFront();

//popFromBack()
//Parameters: None
//Purpose: Removes the last element from the array.
//Return value: None, updates current instance
//Other information: N/A
    void popFromBack();

//removeAt(int index)
//Parameters: The index in the array at which to remove the element
//Purpose: Removes the element from the specified index.
//Return value: Void, updates the current instance
//Other information: N/A
    void removeAt(int index);

//replaceAt(char c, int index)
//Paramters: A char to add to the array and an index at which to add it.
//Purpose: Replaces an element at the given index with the input char
//Return value: Void, updates current instance.
//Other information: N/A
    void replaceAt(char c, int index);

//concatenate(CharArrayList *other)
//Parameters: An ArrayList to add to the current instance
//Purpose: Appends the input ArrayList data array to the current instance's
//         data array
//Return value: Void, updates current instance
//Other information: N/A
    void concatenate(CharArrayList *other);

//shrink()
//Parameters: None
//Purpose: Reduces the size of the array to the bare minimum needed to store
//         its elements.
//Return value: None, updates current instance.
//Other information: All ArrayLists in this program are initialized to -1 in all 
//                   slots when they are allocated. This function detects negative
//                   values and removes them from the lists.
    void shrink();

private: 
    char *data; //a pointer to the data array
    int capacity; //the capacity of the array
    int num_items; //the number of items in the array

//expand()
//Parameters: an integer representing the number of slots to add
//            to the list
//Purpose: Expands the list by the given size
//Return value: Void, updates the current instance
//Other information: Expanded slots are initialized to -1    
    void expand();

//updateCapacity()
//Parameters: None
//Purpose: Checks if the current list needs to be expanded
//Retrun value: None, updates the current list with an expanded copy
    void updateCapacity();

//recycleAndSetData(char *new_data)
//Parameters: The array with which to replace the old array.
//Purpose: Cleans up memory associated with this instance's data array and
//         updates the data pointer to point to the new array
//Other information: N/A
    void recycleAndSetData(char *new_array);
};

#endif
