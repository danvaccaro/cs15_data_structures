/********************************************
 * Comp 15 - Fall 2019
 * Lab 1
 * Julia Lober
 * July 26, 2019
 * Edited by Cicely Panara Fall 2020
 *
 * main.cpp
 * Driver for a grocery list program, keeps track of what
 * items have and have not been purchased from a given input
 *
 * Usage:  shop shoppinglistfile
 *********************************************/


#include "ArrayList.h"
#include <fstream>
#include <iostream>
using namespace std;

bool makeList(ArrayList& toBuy, string filename);
void atStore(ArrayList& toBuy, ArrayList& bought);
void buyItem(ArrayList& toBuy, ArrayList& bought, string item);
void printLists(ArrayList& toBuy, ArrayList& bought);


int main(int argc, char* argv[]) {
    /* print an error message and quit if called incorrectly */
    if (argc != 2) {
        cerr << "Usage: ./shop input.txt\n";
        exit(1);
    } else {
        ArrayList toBuy;
        ArrayList bought;

        if (makeList(toBuy, argv[1])) atStore(toBuy, bought);
    }
}

/*
 * Function makeList
 * Parameters: ArrayList &toBuy - reference to ArrayList to fill in
 *             string filename  - name of file to read
 * Returns: true if successful, false otherwise
 * Does: Puts all the items from the file into the ArrayList toBuy
 */
bool makeList(ArrayList& toBuy, string filename) {
    ifstream in;
    in.open(filename);
    string item;

    /* check for error opening file */
    if (not in.is_open()) {
        cerr << "Error opening file.\n";
        return false;
    }

    /* read file and input information */
    while (getline(in, item))
        toBuy.insert(item);

    in.close();
    return true;
}

/*
 * Function atStore
 * Parameters: ArrayList &toBuy  - shopping  list
 *             ArrayList &bought - purchased list
 * Returns: nothing
 * Does: Handles main functionality of the program, gets user input and
 *       updates lists accordingly
 *
 * TODO:  This function is getting too long.  Refactor?
 */
void atStore(ArrayList& toBuy, ArrayList& bought) {
    string item = "";
    printLists(toBuy, bought);

    cout << "Welcome to the store!"
         << " What are you buying?" << endl
         << "You can always type "
         << "\"Quit\" to leave the store or \"Print\" to show your lists."
         << endl
         << endl;

    while (toBuy.size() > 0) { /* while there are things to buy */
        getline(cin, item);
        if (item == "Print") {
            cout << endl;
            printLists(toBuy, bought);
            cout << "Next item?\n";
        } else if (item == "Quit") {
            cout << "Leaving store!\n\n";
            printLists(toBuy, bought);
            return;
        } else {
            buyItem(toBuy, bought, item);
        }
    }
}

/* Function buyItem
 * Parameters: ArrayList &toBuy  - shopping list
 *             ArrayList &bought - purchased list
 *             string     item   - the item to purchase
 * Returns: nothing
 * Does: If item is found on the toBuy list, add to bought list
 *     otherwise print an error message and leave lists unchanged
 */
void buyItem(ArrayList& toBuy, ArrayList& bought, string item) {
    if (toBuy.remove(item)) { /* if item was on list and thus was removed */
        bought.insert(item);
        if (toBuy.size() != 0) cout << "Next item?\n";
    } else {
        cout << "This item was not on the list,"
             << " try buying something else.\n";
    }
}

/* Function printLists
 * Parameters: ArrayList &toBuy  - shopping list
 *             ArrayList &bought - purchased list
 * Returns: nothing
 * Does: Displays number of items and items on each list on cout
 */
void printLists(ArrayList& toBuy, ArrayList& bought) {
    cout << "Shopping list has " << toBuy.size() << " item(s):\n";
    toBuy.print(cout);
    cout << endl;

    cout << "Purchased " << bought.size() << " item(s):\n";
    bought.print(cout);
    cout << endl;
}
