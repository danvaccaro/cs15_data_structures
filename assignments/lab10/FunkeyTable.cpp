/*
 * FunkeyTable.cpp --- compare two different methods of handling hash
 * table collisions and two different hash functions.
 *
 * your job:  code the insert functions and expand function
 *  our job:  run the insert functions and report results
 *
 * Based on a previous lab by Ben Hescott, I think.
 *
 * Mark A. Sheldon, Tufts University, Spring 2017
 */

#include <iostream>
#include <stdio.h>
#include <functional>

#include "FunkeyTable.h"

using namespace std;

/*
 * Constructor allocates and initializes two empty tables
 * of the INITIAL_TABLE_SIZE
 */
FunkeyTable::FunkeyTable()
{
        currentTableSize = INITIAL_TABLE_SIZE;
        numItemsInTable  = 0;

        chainedTable     = new ChainNode *[currentTableSize];
        linearTable      = new TableEntry[currentTableSize];

        for (int i = 0; i < currentTableSize; i++) {
                chainedTable[i]        = nullptr;
                linearTable[i].isEmpty = true;
        }
}

/*
 * Delete all nodes in list starting with given node
 */
void FunkeyTable::deleteList(ChainNode *node)
{
        //if the list is empty, do nothing
        if (node == nullptr)
                return;
        //delete the rest of the list and then delete the node
        deleteList(node->next);
        delete node;
}

/*
 * destructor
 */
FunkeyTable::~FunkeyTable()
{
        //loop through each list in the table and delete it
        for (int i = 0; i < currentTableSize; ++i) {
                deleteList(chainedTable[i]);
        }
        //free memory associated with both tables
        delete [] chainedTable;
        delete [] linearTable;
}


static size_t good_hash_function(KeyType key)
{
        return std::hash<KeyType>{}(key);
}

static size_t bad_hash_function(KeyType key)
{
        return key.length();
}

static size_t hashValue(KeyType key, FunkeyTable::HashFunction hashFunction)
{
        if (hashFunction == FunkeyTable::BAD_HASH_FUNCTION)
                return bad_hash_function(key);
        else
                return good_hash_function(key);
}

/*
 * Linear Probing
 *
 * Return number of collisions before finding a spot
 *
 */
int FunkeyTable::insertProbing(KeyType key, ValueType value,
                               HashFunction hashFunction)
{
        int    attempt = 0;
        bool   found   = false;
        //hash the key
        size_t hashCode = hashValue(key, hashFunction); 
        //compress the hash
        size_t bucketIndex = hashCode % currentTableSize;
        //loop until we hit an empty slot
        while (not found) {
                //if the slot is empty, fill the key and value and flag as empty
                if (linearTable[bucketIndex].isEmpty == true) {
                        linearTable[bucketIndex].key = key;
                        linearTable[bucketIndex].value = value; 
                        linearTable[bucketIndex].isEmpty = false;
                        //iterate the number of items
                        numItemsInTable++;
                        //report empty slot found
                        found = true;
                }
                //otherwise we hit an occupied slot, iterate the index and attempt count
                else {
                        bucketIndex++;
                        attempt++;
                }
        }
        //expand(hashFunction);
        return attempt;
}

/*
 * Return length of list starting at given node
 */
int FunkeyTable::listLength(ChainNode *nodep)
{
        //recursively count the number of nodes in the list
        if (nodep == nullptr) return 0;
        else return 1 + listLength(nodep->next);
}

/*
 * Chained hashing --- each spot in table is a linked list 
 *
 * Return number of items in that spot before insertion
 */
int FunkeyTable::insertChaining(KeyType key, ValueType value,
                                HashFunction hashFunction)
{
        //hash the key
        size_t hashCode = hashValue(key, hashFunction); 
        //compress the hash
        size_t bucketIndex = hashCode % currentTableSize;
        //store the initial list length
        int initialListLength = listLength(chainedTable[bucketIndex]);
        //insert a new node at the front of the list at the index
        chainedTable[bucketIndex] = 
                new ChainNode(key, value, chainedTable[bucketIndex]);
        //iterate the number of items
        numItemsInTable++;
        //expand(hashFunction);
        //return the initial list length
        return initialListLength;
}




/*
 * Expand both of the hash tables
 */
void FunkeyTable::expand(HashFunction hashFunction)
{
        //calculate load factor and expand if greater than 0.7
        float loadFactor = numItemsInTable/currentTableSize;
        if (loadFactor > 0.7) {
                int oldTableSize = currentTableSize;
                currentTableSize *= 2;
                //store the old tables
                TableEntry *oldLinearTable = linearTable;
                ChainNode **oldChainedTable = chainedTable;
                //instantiate a new table with the new size
                linearTable = new TableEntry[currentTableSize];
                chainedTable = new ChainNode *[currentTableSize];
                //initialize values
                for (int i = 0; i < currentTableSize; ++i) {
                        linearTable[i].isEmpty = true;
                        chainedTable[i] = nullptr;
                }
                // loop through old table
                for (int i = 0; i < oldTableSize; ++i)
                {
                        //if the linear slot isn't empty
                        if (!oldLinearTable[i].isEmpty)
                        {
                                // hash the key
                                size_t linearHashCode = hashValue(oldLinearTable[i].key, hashFunction);
                                // compress the hash
                                size_t linearBucketIndex = linearHashCode % currentTableSize;
                                // copy key/value pairs from old table index i to new table bucketIndex
                                linearTable[linearBucketIndex].key = oldLinearTable[i].key;
                                linearTable[linearBucketIndex].value = oldLinearTable[i].value;
                        }
                        //if the chained slot isn't empty
                        if(oldChainedTable[i] != nullptr) {
                                //hash the key
                                size_t chainHashCode = hashValue(oldChainedTable[i]->key, hashFunction);
                                // compress the hashes
                                size_t chainBucketIndex = chainHashCode % currentTableSize;
                                //instantiate a new node at the new index
                                chainedTable[chainBucketIndex] = 
                                        new ChainNode(oldChainedTable[i]->key, oldChainedTable[i]->value, chainedTable[chainBucketIndex]);
                        }
                }
                //deallocate old tables
                delete [] oldChainedTable;
                delete [] oldLinearTable;
        }
        return;
}

void FunkeyTable::printTableEntry(TableEntry entry)
{
        if (entry.isEmpty)
                cout << "empty";
        else
                cout << "key:  "
                     << entry.key
                     << "; value:  {"
                     << entry.value.chartPosition
                     << ", "
                     << entry.value.bpm
                     << "}";
}

void FunkeyTable::printChainNode(ChainNode *nodep)
{
        cout << "key:  " << nodep->key
             << "; value:  {" << nodep->value.chartPosition
             << ", " << nodep->value.bpm << "}";
}

/*
 * Print both hash tables
 * Could break this up into two print functions
 */
void FunkeyTable::print()
{
        cout << "Linear table" << endl;
        
        for (int i = 0; i < currentTableSize; ++i) {
                cout << i << ":  ";
                printTableEntry(linearTable[i]);
                cout << endl;
        }
        cout << endl << "Chained table" << endl;
        
        for (int i = 0; i < currentTableSize; ++i) {
                ChainNode *curr = chainedTable[i];
                cout << i << ":  [ ";
                while (curr != NULL) {
                        printChainNode(curr);
                        curr = curr->next;
                        if (curr != NULL)
                                cout << ", ";
                }
                cout << "]" << endl;
        }
        cout << endl;
}
