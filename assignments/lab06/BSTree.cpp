/*
 * Implementation of BST (Binary Search Tree) class with integer keys
 * Data Structures BST lab
 */

#include <cstdlib>
#include <iostream>
#include <queue>
#include <stack>

#include "BSTree.h"

using namespace std;

//
// A couple handy functions for creating new, initialized nodes.
// We could make constructors for the struct, but let's keep things
// simple.
//

//
// Return a pointer to a newly allocated node initialized with given
// values.
//
BST::BSTNode *BST::newBSTNode(int v, BSTNode *left, BSTNode *right) {
    BST::BSTNode *newNode = new BSTNode;
    newNode->value        = v;
    newNode->left         = left;
    newNode->right        = right;

    return newNode;
}

//
// Return a pointer to a newly allocated leaf node with value v.
//
BST::BSTNode *BST::newBSTNode(int v) {
    return newBSTNode(v, nullptr, nullptr);
}

//
// Initialize an empty tree.
//
BST::BST() {
    root = nullptr;
}

//
// Delete all the nodes in the tree
//
BST::~BST() {
    postOrderDelete();
}

//
// isEmpty:
//     Return true if tree with given root is empty and false otherwise
//
bool BST::isEmpty(BSTNode *root) {
    return root == nullptr;
}

//
// Insert: public version of Insert takes a value only and
//         inserts it into the tree at the root
//
void BST::unbalancedInsert(int v) {
    root = unbalancedInsert(root, v);
}

//
// Insert: (private version) inserts a value in the tree rooted at r
//
//   Return the root of current tree with the value inserted
//
//   note: ALWAYS adds a leaf.
//
//   Implementation notes:
//       - When the base case is reached, we are inserting the value
//         into an empty tree, i. e., r is nullptr.
//         In this case, we create a new leaf node with the given data
//         value and return a pointer to that.  If the caller had a
//         non-empty tree node, then they will set the corresponding
//         subtree in their node to the result.
//         DRAW THIS OUT!
//       - Duplicate keys will go into right branch here, i. e., the
//         left subtree contains values < node's key, right subtree
//         contains values >= node's key.
//
BST::BSTNode *BST::unbalancedInsert(BSTNode *r, int v) {
    if (r == nullptr) {
        return newBSTNode(v);
    } else if (v < r->value) {
        r->left = unbalancedInsert(r->left, v);
        return r;

    } else {
        r->right = unbalancedInsert(r->right, v);
        return r;
    }
}


//****************** inorder *****************//

//
// Perform an in-order print starting at the root of the entire tree
//
void BST::inOrder() {
    inOrder(root); // calls the next one
}

//
// Perform an in-order print of the subtree rooted at the given node
//
void BST::inOrder(BSTNode *root) {
    //if there is a left subtree, print it
    if (root->left != nullptr) 
        inOrder(root->left);
    //print the root
    std::cout << root->value << " ";
    //if there is a right tree, print it
    if (root->right != nullptr)
        inOrder(root->right);
}


//****************** postorder *****************//

//
// Perform post-order traversal to delete the entire tree
//
void BST::postOrderDelete() {
    postOrderDelete(root);
}

//
// Perform post-order traversal to delete tree rooted at give node
// Question to ponder:  Could we use another traversal to delete the
//                      tree?
//
void BST::postOrderDelete(BSTNode *root) {
    //if the tree is empty, do nothing
    if (root == nullptr)
        return;
    //delete the left tree
    postOrderDelete(root->left);
    //delete the right tree
    postOrderDelete(root->right);
    //delete the root node
    delete root;
}


//****************** preorder *****************//

//
// Perform a pre-order print of the entire tree.
// Question to ponder:  Can we do this without a helper function?
//
void BST::preOrder() {
    preOrder(root); // calls the next function (really needed?)
}

//
// Perform a pre-order print of the subtree rooted at given node.
// Uses a stack from the STL rather than the C++ run time stack.
//
void BST::preOrder(BSTNode *root) {
    // initialize a stack of node pointers
    stack<BSTNode *> treeStack;
    //check if root is nullptr
    if (root == nullptr) return;
    //push the root to the top of the stack
    treeStack.push(root);
    //loop until stack is empty
    while (!treeStack.empty()) {
        //store a pointer to the top of the stack
        BSTNode *aNode = treeStack.top();
        //print the value of the node
        std::cout << aNode->value << " ";
        //remove the node from the stack
        treeStack.pop();
        //if there is a node to the right, push it to the top of the stack
        if (aNode->right != nullptr)
            treeStack.push(aNode->right);
        //if there is a node to the left, push it to the top of the stack
        if (aNode->left != nullptr)
            treeStack.push(aNode->left);
    }
}


//****************** levelorder *****************//

//
// Perform a level-order print of the entire tree
//
void BST::levelOrder() {
    levelOrder(root);
}

//
// Perform a level-order print of the subtree rooted at the given node
// Uses a queue from the STL
//
void BST::levelOrder(BSTNode *root) {
    //initialize a queue
    queue<BSTNode *> treeQueue;
    //push the root to the back of the queue
    treeQueue.push(root);
    //loop until the queue is empty
    while (!treeQueue.empty()) {
        //store the node at the front of the queue
        BSTNode *aNode = treeQueue.front();
        //print the node value
        std::cout << aNode->value << " ";
        //remove the node from the queue
        treeQueue.pop();
        //if there is a node to the left, push it to the queue
        if (aNode->left != nullptr)
            treeQueue.push(aNode->left);
        //if there is a node to the right, push it
        if (aNode->right != nullptr) 
            treeQueue.push(aNode->right);
    }
}
