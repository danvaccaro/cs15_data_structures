/* Comp 15 Lab 9: Heaps
 *
 * A class that organizes a collection of strings into a min-heap
 *
 * O(n log n) construction (can be O(n) if you use algorithm from class!
 * O(log n)   insertion
 * O(1)       to access minimum element
 * O(log n)   to remove minimum element.
 */

#include <string>

using std::string;

class Heap
{
public:
        Heap();
        ~Heap();

        // Build a heap from array
        Heap(string list[], int listSize);

        // insert s into heap, not used for this lab
        void insert(string s);

        // return minimum element, not used for this lab
        string min();

        // remove and return smallest element in heap
        string removeMin();

        // return size of heap;
        int size();

private:
        // Heap is implemented as an array list
        static const int INIT_SIZE = 100;

        string *heap;            // pointer to array with heap data
        int     heapSize;        // # elements currently in heap
        int     maxCapacity;     // current max capacity

        //
        // down heap function is recursive and
        // works with the location of the element
        // in the tree.  heap[location] stores
        // the value being inserted
        //
        void downHeap(int location);

        //
        // up heap function for insert
        //
        // elemet was originally inserted into first open
        // spot in tree, wich is the first available slot in array
        // (satisfies shape invariant).
        //
        // upHeap bubbles element up to the proper spot
        // (fixes heap invariant)
        //
        void upHeap(int location);

        //
        // build heap function used by constructor that takes in an array
        // and turns the array into a heap (aka "heapify")
        //
        void buildHeap();

        //
        // abstract away calculations for child/parent relationships
        //
        int  leftChild(int index);
        int  rightChild(int index);
        int  parent(int index);

        //
        // Upon return, capacity of array is >= desiredCapacity
        //
        void ensureCapacity(int desiredCapacity);
};
