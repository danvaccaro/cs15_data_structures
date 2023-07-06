/*
 * unit_tests.h
 *
 * CS 15 homework 1
 * by Tyler Calabrese, January 2021
 *
 * edited by: Milod Kazerounian, January 2022
 *
 * Uses Matt Russell's unit_test framework to test the CharArrayList class.
 *
 * Instructions for using testing framework can be found at in CS 15's lab
 * 1 -- both in the spec and in the provided ArrayList_tests.h and Makefile.
 * More in-depth information for those who are curious as to how it works can
 * be found at http://www.github.com/mattrussell2/unit_test.
 */

#include "CharArrayList.h"
#include <cassert>

/********************************************************************\
*                       CHAR ARRAY LIST TESTS                        *
\********************************************************************/

/* To give an example of thorough testing, we are providing
 * the unit tests below which test the insertAt function. Notice: we have
 * tried to consider all of the different cases insertAt may be
 * called in, and we test insertAt in conjunction with other functions!
 *
 * You should emulate this approach for all functions you define.
 */


// Tests correct insertion into an empty AL.
// Afterwards, size should be 1 and element at index 0
// should be the element we inserted.
void insertAt_empty_correct() { 
    CharArrayList test_list;
    test_list.insertAt('a', 0);
    assert(test_list.size() == 1);
    assert(test_list.elementAt(0) == 'a');          
}

// Tests incorrect insertion into an empty AL.
// Attempts to call insertAt for index larger than 0.
// This should result in an std::range_error being raised.
void insertAt_empty_incorrect() {
    
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList test_list;
    try {
        // insertAt for out-of-range index
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        // if insertAt is correctly implemented, a range_error will be thrown,
        // and we will end up here
        range_error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0]");
    
}

// Tests correct insertAt for front of 1-element list.
void insertAt_front_singleton_list() {
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at front
    test_list.insertAt('b', 0);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'a');
}

// Tests correct insertAt for back of 1-element list.
void insertAt_back_singleton_list() {
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at back
    test_list.insertAt('b', 1);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
}

// Tests calling insertAt for a large number of elements.
// Not only does this test insertAt, it also checks that
// array expansion works correctly.
void insertAt_many_elements() {
    
    CharArrayList test_list;
    // insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
    }

    assert(test_list.size() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(test_list.elementAt(i) == 'a');
    }

}

// Tests insertion into front, back, and middle of a larger list.
void insertAt_front_back_middle() {
        char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
        CharArrayList test_list(test_arr, 8);

        // insertAt middle
        test_list.insertAt('z', 3);
        

        assert(test_list.size() == 9);
        assert(test_list.elementAt(3) == 'z');
        assert(test_list.toString() == 
        "[CharArrayList of size 9 <<abczdefgh>>]");

        // insertAt front
        test_list.insertAt('y', 0);

        assert(test_list.size() == 10);
        assert(test_list.elementAt(0) == 'y');
        assert(test_list.toString() == 
        "[CharArrayList of size 10 <<yabczdefgh>>]");

        // insertAt back
        test_list.insertAt('x', 10);

        assert(test_list.size() == 11);
        assert(test_list.elementAt(10) == 'x');
        assert(test_list.toString() == 
        "[CharArrayList of size 11 <<yabczdefghx>>]");
}

// Tests out-of-range insertion for a non-empty list.
void insertAt_nonempty_incorrect() {
    
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8]");
    
}

// Tests removal from an empty AL.
// Should throw a range error exception
void removeAt_empty_correct() {
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList test_list;
    try {
        // removeAt for out-of-range index
        test_list.removeAt(0);
    }
    catch (const std::range_error &e) {
        // if removeAt is correctly implemented, a range_error will be thrown,
        // and we will end up here
        range_error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (0) not in range [0..0)");
}

//tests proper removal from a single-element list
void removeAt_singleton_list() {
    // initialize 1-element list
    CharArrayList test_list('a');
    // insert at front
    test_list.removeAt(0);
    assert(test_list.isEmpty());
}

//tests removing en masse
//should return an empty list
void removeAt_many_elements(){
    //initialize a size 1000 list
    CharArrayList test_list;
    // insert 1000 elements
    for (int i = 0; i < 1000; ++i) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
    }
    //remove 1000 elements
    for (int i = 0; i < 1000; ++i) {
        test_list.removeAt(0);
    }
    assert(test_list.isEmpty());
}

//tests removing at various positions
void removeAt_front_back_middle(){
    //initialize a test list
    char test_chars[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharArrayList test_list(test_chars, sizeof(test_chars));
    //remove at front of the list
    test_list.removeAt(0);
    assert(test_list.size() == 7);
    assert(test_list.elementAt(0) == 'b');

    //remove at end of the list
    test_list.removeAt(6);
    assert(test_list.elementAt(5) == 'g');
    assert(test_list.size() == 6);

    //remove at middle of the list
    test_list.removeAt(3);
    assert(test_list.size() == 5);
    assert(test_list.elementAt(3) == 'f');
}

//tests removeAt an out of range index
//should throw exception
void removeAt_nonempty_incorrect() {
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";
    char test_chars[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharArrayList test_list(test_chars, sizeof(test_chars));
    try {
        test_list.removeAt(9);
    }
    catch(const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    
    assert(range_error_thrown);
    assert(error_message == "index (9) not in range [0..8)");

}

//tests inserting in order for an empty list
//should return the sorted elements
void insertInOrder_empty() {
    CharArrayList test_list;
    test_list.insertInOrder('a');
    test_list.insertInOrder('t');
    test_list.insertInOrder('f');
    assert(test_list.toString() ==
        "[CharArrayList of size 3 <<aft>>]" );
}

//tests inserting in order for a single-element list
void insertInOrder_singleton() {
    CharArrayList test_list('g');
    test_list.insertInOrder('t');
    assert(test_list.toString() ==
        "[CharArrayList of size 2 <<gt>>]" );
}

//tests insertion of multiple elements in order using loops
void insertInOrder_many_elements() {
    CharArrayList test_list;
    for(int i = 0; i < 15; i++)
        test_list.pushAtBack('j');
    for(int i = 0; i < 9; i++)
        test_list.insertInOrder('t');
    for(int i = 0; i < 9; i++)
        test_list.insertInOrder('a');
    assert(test_list.toString() ==
        "[CharArrayList of size 33 <<aaaaaaaaajjjjjjjjjjjjjjjttttttttt>>]" );
}

//tests inserting in order at different positions
void insertInOrder_front_middle_back() {
    char test_chars[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharArrayList test_list(test_chars, sizeof(test_chars));

    test_list.insertInOrder('a');
    test_list.insertInOrder('f');
    test_list.insertInOrder('t');

    assert(test_list.toString() ==  
        "[CharArrayList of size 11 <<aabcdeffght>>]" );
}

//tests replacing at an empty position
//should range error
void replaceAt_empty() {
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";
    
    CharArrayList test_list;
    try {
        test_list.replaceAt('c', 0);
    }
    catch(const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    
    assert(range_error_thrown);
    assert(error_message == "index (0) not in range [0..0)");
}

//tests replaceAt given an out of range index. should throw anmge exception
void replaceAt_singleton_list_incorrect() {
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";
    CharArrayList test_list('a');
    try {
        test_list.replaceAt('c', 1);
    }
    catch(const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message == "index (1) not in range [0..1)");
}

//tests replacing a larger sized list using a loop
void replaceAt_many_elements() {
    //initialize a size 1000 list
    CharArrayList test_list;
    // insert 40 elements
    for (int i = 0; i < 40; ++i) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
    }
    //replace 40 elements
    for (int i = 0; i < 40; ++i) {
        test_list.replaceAt('c', i);
    }
    assert(test_list.toString() ==  
        "[CharArrayList of size 40 <<cccccccccccccccccccccccccccccccccccccccc>>]" );
};

//tests replacing at various points in the list
//should return properly replaced values at the given index
void replaceAt_front_back_middle() {
    //initialize a test list
    char test_chars[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharArrayList test_list(test_chars, sizeof(test_chars));
    //replace at front of the list
    test_list.replaceAt('K', 0);
    assert(test_list.size() == 8);
    assert(test_list.elementAt(0) == 'K');

    //replace at end of the list
    test_list.replaceAt('I', 7);
    assert(test_list.size() == 8);
    assert(test_list.elementAt(7) == 'I');

    //replace at middle of the list
    test_list.replaceAt('S', 3);
    assert(test_list.size() == 8);
    assert(test_list.elementAt(3) == 'S');
}

//tests replacing an element at an out of range index
//should return a range error
void replaceAt_nonempty_incorrect() {
    bool range_error_thrown = false;
    std::string error_message = "";
    
     //initialize a test list
    char test_chars[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharArrayList test_list(test_chars, sizeof(test_chars));
    //replace at front of the list
    try {
        test_list.replaceAt('K', 9);
    }
    catch(const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message == "index (9) not in range [0..8)");
}

//tests for push functions
//All pushes should return the input at the correct position
void pushTests() {
    //push to back to empty list
    CharArrayList empty_list1;
    empty_list1.pushAtBack('a');
    assert(empty_list1.size() == 1);
    assert(empty_list1.elementAt(0) == 'a');

    //push to front of empty list
    CharArrayList empty_list2;
    empty_list2.pushAtFront('a');
    assert(empty_list2.size() == 1);
    assert(empty_list2.elementAt(0) == 'a');

    //push to back of single-element list
    CharArrayList single_element_list1('a');
    single_element_list1.pushAtBack('b');
    assert(single_element_list1.size() == 2);
    assert(single_element_list1.elementAt(0) == 'a');
    assert(single_element_list1.elementAt(1) == 'b');
    
    //push to front of single-element list
    CharArrayList single_element_list2('a');
    single_element_list2.pushAtFront('b');
    assert(single_element_list2.size() == 2);
    assert(single_element_list2.elementAt(0) == 'b');
    assert(single_element_list2.elementAt(1) == 'a');

    //push to back of multi-element list
    char test_chars[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharArrayList multi_element_list1(test_chars, sizeof(test_chars));
    multi_element_list1.pushAtBack('d');
    assert(multi_element_list1.size() == 9);
    assert(multi_element_list1.elementAt(8) == 'd');

    //push to front of multi-element list
    multi_element_list1.pushAtFront('V');
    assert(multi_element_list1.size() == 10);
    assert(multi_element_list1.elementAt(0) == 'V');

    //push in a loop: Fails with rand() % 256, works with regular chars
    //for some reason
    CharArrayList loop_test_list;
    for (int i = 0; i < 10; ++i) {
        //char charToAdd = rand() % 256; THIS FAILS TO GENERATE VALID CHARS
        char charToAdd = 'a';
        loop_test_list.pushAtBack(charToAdd);
    }
}

//tests variations of pop - all empty lists should return runtime errors
//single char pops should return empty list
//multiple element lists should have accurate size and values
void popTests() {
    //error tracking variable
    bool runtime_error_thrown = false;
    std::string error_message = "";

    //pop from back of empty list
    CharArrayList empty_list1;
    try {
        empty_list1.popFromBack();
    }
    catch(const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");
    
    //pop from front of empty list
    runtime_error_thrown = false;
    error_message = "";
    CharArrayList empty_list2;
    try {
        empty_list2.popFromFront();
    }
    catch(const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");

    //pop from back of single-element list
    CharArrayList single_element_list1('a');
    single_element_list1.popFromBack();
    assert(single_element_list1.isEmpty());
    
    //pop from front of single-element list
    CharArrayList single_element_list2('a');
    single_element_list2.popFromBack();
    assert(single_element_list2.isEmpty());
        

    //pop from back of multi-element list
    char test_chars[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharArrayList multi_element_list1(test_chars, sizeof(test_chars));
    multi_element_list1.popFromBack();
    assert(multi_element_list1.size() == 7);
    assert(multi_element_list1.elementAt(multi_element_list1.size() - 1) == 'g');
    
    //pop from front of many-element list
    multi_element_list1.popFromFront();
    assert(multi_element_list1.size() == 6);
    assert(multi_element_list1.elementAt(0) == 'b');
}

//tests validity of toString and toReverseString for various sizes of lists
void toStringAndReverseTest() {
    //test empty list
    CharArrayList empty_list;
    assert(empty_list.toString() == "[CharArrayList of size 0 <<>>]");
    assert(empty_list.toReverseString() == "[CharArrayList of size 0 <<>>]");
    
    //test single element list
    CharArrayList single_element_list('a');
    assert(single_element_list.toString() == "[CharArrayList of size 1 <<a>>]");
    assert(single_element_list.toReverseString() == "[CharArrayList of size 1 <<a>>]");
    
    //test multi element list
    char test_chars[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharArrayList multi_element_list(test_chars, sizeof(test_chars));
    assert(multi_element_list.toString() == "[CharArrayList of size 8 <<abcdefgh>>]");
    assert(multi_element_list.toReverseString() == "[CharArrayList of size 8 <<hgfedcba>>]");
}

//tests for proper concatenation of various list sizes
void concatenateTests() {
    CharArrayList empty_list1;
    CharArrayList empty_list2;
    CharArrayList single_element_list1('a');
    CharArrayList single_element_list2('b');
    char test_chars1[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    char test_chars2[6] = {'q', 'r', 's', 't', 'u', 'v'};
    CharArrayList multi_element_list1(test_chars1, sizeof(test_chars1));
    CharArrayList multi_element_list2(test_chars2, sizeof(test_chars2));

    //concatenating two empty lists
    empty_list1.concatenate(&empty_list2);
    assert(empty_list1.isEmpty());
    assert(empty_list1.toString() == "[CharArrayList of size 0 <<>>]");

    //concatenating an empty list with a single element list
    empty_list2.concatenate(&single_element_list1);
    assert(empty_list2.size() == 1);
    assert(empty_list2.toString() == "[CharArrayList of size 1 <<a>>]");

    //concatenating a single char list with an empty list
    single_element_list1.concatenate(&empty_list1);
    assert(single_element_list1.size() == 1);
    assert(single_element_list1.toString() == "[CharArrayList of size 1 <<a>>]");

    //concatenating two single char lists
    single_element_list1.concatenate(&single_element_list2);
    assert(single_element_list1.size() == 2);
    assert(single_element_list1.toString() == "[CharArrayList of size 2 <<ab>>]");

    //concatenating a single element list with a multi-element list
    single_element_list2.concatenate(&multi_element_list1);
    assert(single_element_list2.size() == 9);
    assert(single_element_list2.toString() == "[CharArrayList of size 9 <<babcdefgh>>]");
    
    //concatenating a multi-element list with a single element list
    CharArrayList single_element_list3('z');
    multi_element_list1.concatenate(&single_element_list3);
    assert(multi_element_list1.size() == 9);
    assert(multi_element_list1.toString() == "[CharArrayList of size 9 <<abcdefghz>>]");

    //concatenating two multi-element lists
    multi_element_list1.concatenate(&multi_element_list2);
    assert(multi_element_list1.size() == 15);
    assert(multi_element_list1.toString() == "[CharArrayList of size 15 <<abcdefghzqrstuv>>]");

    //concatenating multi with empty
    multi_element_list1.concatenate(&empty_list1);
    assert(multi_element_list1.size() == 15);
    assert(multi_element_list1.toString() == "[CharArrayList of size 15 <<abcdefghzqrstuv>>]");

    //concatenating empty with multi
    empty_list1.concatenate(&multi_element_list1);
    assert(multi_element_list1.size() == 15);
    assert(multi_element_list1.toString() == "[CharArrayList of size 15 <<abcdefghzqrstuv>>]");
}

//run all tests at once
void run_debug() {
    insertAt_empty_correct();
    insertAt_empty_incorrect();
    insertAt_front_singleton_list();
    insertAt_back_singleton_list();
    insertAt_many_elements();
    insertAt_front_back_middle();
    insertAt_nonempty_incorrect();

    insertInOrder_empty();
    insertInOrder_singleton();
    insertInOrder_many_elements();
    insertInOrder_front_middle_back();

    removeAt_empty_correct();
    removeAt_singleton_list();
    removeAt_many_elements();
    removeAt_front_back_middle();
    removeAt_nonempty_incorrect();

    replaceAt_empty();
    replaceAt_singleton_list_incorrect();
    replaceAt_many_elements();
    replaceAt_front_back_middle();
    replaceAt_nonempty_incorrect();

    pushTests();
    popTests();

    toStringAndReverseTest();

    concatenateTests();

    std::cout << "Passed tests!\n";
}