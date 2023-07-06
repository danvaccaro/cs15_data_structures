/*
 * Filename: AVLTree.h
 * Contains: Interface of AVL Trees for Comp 15
 * Part of: Lab assignment "AVL Trees" for Comp 15
 *
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <iostream>

/*
 * AVL Tree Node:
 * - data is the value stored in the node
 * - height is the height of the node within the tree, increasing 
 *          from leaf up to the root.
 *
 * We're defining node struct outside the class, which is not good!
 * Node now available in the client's name space.  Our abstraction is
 * sound still, since we don't give the client access to Nodes, but
 * now the client can't use the name Node for anything!
 * This goes against the spirit of data abstraction.
 * We decided to do it this way because we are using a pretty printer Function
 * outside this class (complicated and indeepndent of the rest of the class). 
 * Keep in mind that this is a bad policy and not do it in your assignments
 * We will take deductions for abstraction violations when we assess
 * your submission.
*/

struct Node {
        int   data;
        int   height;
        Node *left;
        Node *right;
};

/* defined in pretty_print.cpp */
void printPretty(Node *root, int level, int indentSpace, std::ostream &out);

class AVLTree {
public:
        /* constructor */
        AVLTree();

        /* destructor */
        ~AVLTree();

        /*
         * insert() inserts the value into the AVL Tree and balances the
         * tree with each insertion.
         * If the value is already in the tree, the node doesnt 
         * add it. You must write helper functions for this to work
         */
        void insert(int value);

        /*
         * Removes the node whose value matches the one given by parameter 
         * Must rebalance the tree after the deletion
         * To be implemented by the students for bonus points
        */
        bool remove(int value);

        /* prints the tree in cout */
        void print_tree() const;

private:
        /* the root of the tree (starts as nullptr) */
        Node *root;

        /*
         * the following seven functions are private helper functions
         * for the public functions. We do not want to expose the
         * internals of the tree publicly, so we pass the root (and
         * other information in some cases) to the functions below
         * from the public functions.
        */
        Node *insert(Node *node, int value);
        bool  remove(Node *node, int value);
        Node *balance(Node *node);
        Node *rightRotate(Node *node);
        Node *leftRotate(Node *node); 
        int heightDiff(Node *node); 
        int nodeHeight(Node *node); 

        /* used by the destructor to delete nodes recursively */
        void  post_order_delete(Node *node);

};


#endif /* AVLTREE_H_ */
