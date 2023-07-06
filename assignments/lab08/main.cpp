/*
 * Comp 15:  Heap lab
 *
 * Uses a heap implementation to sort an array of strings.
 */

#include <iostream>

#include "heap.h"

using namespace std;

/*
 * Sort the given string list:  updates the list to be in
 * sorted order.
 *
 * Implementation note:  Uses a heap.
 */
void heapSort(string list[], int size) {
    string *temp;
    temp = new string[size];

    // make a heap from the original list
    Heap h(list, size);

    
    // copy a sorted version into temp
    for (int i = 0; i < size; i++) {
        temp[i] = h.removeMin();
    }


    // copy back into orginal list
    // not space efficient as it uses
    // a second array --- a third if you
    // count the heap
    for (int j = 0; j < size; j++) {
        list[j] = temp[j];
    }
    delete[] temp;
}

int main() {
    string testList[] = {
        "comparison",  "fashion", "make",     "prom,",       "beyond",
        "extravagant", "her",     "deserves", "invitation,", "rachel?",
        "for",         "night:",  "my",       "a",           "beauty"};
    int size = sizeof(testList) / sizeof(string);
    heapSort(testList, size);

    cout << " Words in the list should be in"
         << " lexicographic (dictionary) order:" << endl
         << endl;

    for (int i = 0; i < size; i++) {
        cout << testList[i] << " ";
    }
    cout << endl;

    return 0;
}

