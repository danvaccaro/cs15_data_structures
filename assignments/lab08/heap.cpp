/* Comp 15 Lab 9: Heaps 
 * Implementation of Heap class with string keys
 * Updated 11/2/2020 by Ellis Brown
 * Edited by: 
 */

#include <iostream>

#include "heap.h"

using namespace std;

/*
 * Default constructor
 */
Heap::Heap()
{
        heap        = new string[INIT_SIZE];
        heapSize    = 0;
        maxCapacity = INIT_SIZE;
}

/*
 * Destructor
 */
Heap::~Heap()
{
        // TODO: your code here
}

/*
 * intialize a heap from an array
 */
Heap::Heap(string list[], int listSize)
{
        heap        = new string[listSize + 1];
        maxCapacity = listSize + 1;

        // Remember our implementation of a heap
        // starts at 1 not zero, so we store a
        // nonce value at index 0.
        // Don't use the fact that this value is there:
        // Clients could store this string in their heap!
        // Just remember index 0 is not used
        heap[0] = "I'M NOT PART OF THE HEAP";

        // copy the unsorted list over
        for (int i = 0; i < listSize; i++) {
                heap[i + 1] = list[i]; //notice indexing
        }
        heapSize = listSize;
        // use the build heap function
        // to make unsorted array into a heap
        buildHeap();
}

/*
 * insert a string into the heap. 
 * requires the function upHeap to be implemented
 */
void Heap::insert(string s)
{
        // NB:  We do not use slot zero in the array
        // The array is thus already of size (heapSize + 1)
        // But we want to add one more element, so we
        // need an array of size (heapSize + 2)
        ensureCapacity(heapSize + 2);

        // first, satisfy the shape invariant:
        // location to insert is heapSize + 1
        // (Recall, 0th location not used)
        heap[heapSize + 1] = s;
        heapSize++;

        // re-establish the heap invariant
        //heapSize is the index with our inserted element
        upHeap(heapSize); 
}

/*
 * return smallest element in heap
 */
string Heap::min()
{       
        //return the element at index 1
        return heap[1];
}

/*
 * remove and return smallest element in heap
 */
string Heap::removeMin()
{
        //store the element at index 1
        std::string minValue = min();
        //replace the min value with the value at heapSize
        heap[1] = heap[heapSize];
        //decrement the size
        heapSize--;
        //downheap from the root
        downHeap(1);

        return minValue;
}

/*
 * return size of heap
 */
int Heap::size()
{
        return heapSize;
}

/*
 * downHeap establishes/verifies heap invariant from given 
 * location down to leaves
 * if parent is out of order with respect to children,
 * swap with smaller child and downHeap from updated child
 */
void Heap::downHeap(int location)
{
        //bool to track whether sort is complete
        bool done = false;
        //estavlish the initial index as the smallest index
        int smallestIndex = location;
        //continue sorting until index doesn't changr
        while(!done) {
                //store the original index and its children
                int oldSmallestIndex = smallestIndex;
                int leftChildIndex = 2 * smallestIndex;
                int rightChildIndex = (2 * smallestIndex) + 1;
                //if there is a left child in bounds and it is smaller than the parent, set the
                //smallest index to the left child
                if (leftChildIndex <= heapSize
                    && heap[leftChildIndex][0] < heap[smallestIndex][0])
                        smallestIndex = leftChildIndex;                
                //if there is a right child in bounds and it is smaller than the parent, set the
                //smallest index to the right child
                if (rightChildIndex <= heapSize
                    && heap[rightChildIndex][0] < heap[smallestIndex][0])
                        smallestIndex = rightChildIndex; 
                //if the smallest index didn't change, end the loop  
                if (smallestIndex == oldSmallestIndex) {
                        done = true;
                }
                //otherwise the smallest index changed
                else {
                        //store the value at the index to downheap
                        std::string temp = heap[location];
                        //swap the value at the location with the smaller child
                        heap[location] = heap[smallestIndex];
                        //set the value of the smaller child to the downheaped value
                        heap[smallestIndex] = temp;
                        //downheap from the new smallest index
                        downHeap(smallestIndex);
                }
        }
        return;
}

/* NOT required for this lab, but you can write it if you have time
 * upHeap reestablishes heap invariant from given node to root
 * If child is out of order with respect to parent, swap and
 * continue to upHeap from parent to root
 */
void Heap::upHeap(int location)
{
        (void) location; // Removes compiler warning about unused variable.
}

/*
 * creates a heap out of the unsorted array.
 * Naive algorithm is O(n log n)
 * Algorithm from class/prelab is O(n) (proof in 160)
 */
void Heap::buildHeap()
{      
        for (int i = (heapSize / 2); i > 0; --i)
                downHeap(i);
                
}

/*
 * Return left child for element at given index
 */
int Heap::leftChild(int index)
{
        return index * 2;
}

/*
 * Return right child for element at given index
 */
int Heap::rightChild(int index)
{
        return (index * 2) + 1;

}

/*
 * Return the parent for element at given index
 */
int Heap::parent(int index)
{
        return index / 2; // note integer division
}

/* 
 * Purpose: Ensure heap array has at least the desired capacity.
 */
void Heap::ensureCapacity(int desiredCapacity)
{
        if (maxCapacity >= desiredCapacity)
                        return;  // Nothing to do:  array is big enough

        // otherwise, expand
        int     newCapacity = max(desiredCapacity, 2 * maxCapacity + 2);
        string *newArray    = new string[newCapacity];

        // dutifully copying unused slot 0
        // Note elements occupy slots 1 .. heapSize, inclusive
        for (int i = 0; i < heapSize + 1; ++i) {
                newArray[i] = heap[i];
        }
        
        maxCapacity = newCapacity;
        delete [] heap;
        heap = newArray;
}


// Comp cat
// =^.^=
