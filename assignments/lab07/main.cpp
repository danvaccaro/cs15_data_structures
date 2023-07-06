/*
 * Filename: main.cpp
 * Contains: Driver for lab session about AVL Trees for COMP15
 * Part of: Lab assignment "AVL Trees" for Comp 15 Fall 2018
 *
 */

#include <iostream>
#include "AVLTree.h"

using namespace std;

void print_tree_details(AVLTree &avl)
{
        avl.print_tree();
}

int main()
{
        AVLTree avl;
        //int values[]  = {10,9,8,7,6,5,4,3,2,1,0,-1, -2, -3, -4};
        int values[]  = {3, 2, 1, 5, 4, 5, 6, 7, 16, 15, 14, 13, 12,
                         11, 10, 9, 8}; 
        // Use the second one once the tree is balanced

        //Tricky:  won't work for array params
        int numValues = sizeof(values) / sizeof(int);

        cout << "Inserting nodes into tree\n";
        for (int i = 0; i < numValues; i++) {
                std::cerr << "inserting " << values[i] << "\n";
                avl.insert(values[i]);
                print_tree_details(avl);

        }
        cout << "Resulting tree\n";
        print_tree_details(avl);


        cout << "\nFinished!\n";

        return 0;
}
