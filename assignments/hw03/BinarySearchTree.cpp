/* Dan Vaccaro
 * BinarySearchTree.cpp
 * CS 15
 * Date: 3/11/2023
 *
 * Implementation of the Binary Search Tree class.
 * Behaves like a standard BST except that it handles multiplicity
 * If you insert a number twice  and then remove it once, then it will
 * still be in the data structure
 */

#include <cstring>
#include <iostream>
#include <limits>

#include "BinarySearchTree.h"

using namespace std;

//Default constructor
//Instantiates an empty tree.
BinarySearchTree::BinarySearchTree() {
    //set the root of the new tree to nullptr
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    // walk tree in post-order traversal and delete
    post_order_delete(root);
    root = nullptr; // not really necessary, since the tree is going
                    // away, but might want to guard against someone
                    // using a pointer after deleting
}
//post_order_delete
//Purpose: Deletes the tree from memory
//Paramters: A node to start deleting from.
//Returns: void, sets the tree root to nullptr.
void BinarySearchTree::post_order_delete(Node *node) {
    //Base case: if the tree is empty, do nothing
    if (node == nullptr) {
        return;
    }
    //delete the left tree
    post_order_delete(node->left);
    //delete the right tree
    post_order_delete(node->right);
    //delete the current node
    delete node;
    //set root to nullptr
    root = nullptr;
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source) {
    // use pre-order traversal to copy the tree
    root = pre_order_copy(source.root);
}

// assignment overload
BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &source) {
    //check for self-assignment
    if (&source != this) {
        // delete current tree if it exists
        post_order_delete(root);
        //set the root to null
        root = pre_order_copy(source.root);
    }
    //return a reference to this tree
    return *this;
}
//pre_order_copy
//Purpose: Generates a deep copy of a tree rooted at the input node.
//Paramters: A node to start copying from
//Returns: A pointer to the root of the copy.
BinarySearchTree::Node *BinarySearchTree::pre_order_copy(Node *node) const {
    //Base case: if the tree is empty, return null
    if (node == nullptr) {
        return nullptr;
    }
    else {
        //instantiate a new node to copy data into 
        Node *nodeCopy = new Node;
        //copy data into new node
        nodeCopy->data = node->data;
        //copy count into the new node
        nodeCopy->count;
        //copy the left tree
        nodeCopy->left = pre_order_copy(node->left);
        //copy the right tree
        nodeCopy->right = pre_order_copy(node->right);
        //return a pointer to the node copy
        return nodeCopy;
    }
}

int BinarySearchTree::find_min() const {
    if (root == nullptr) return numeric_limits<int>::max(); // INT_MAX

    return find_min(root)->data;
}
//find_min
//Purpose: Finds the minimum value in the tree
//Parameters: A node to start from
//Returns: A pointer to the node containing the min value
BinarySearchTree::Node *BinarySearchTree::find_min(Node *node) const {
    //if the node is null, return null
    if (node == nullptr)
        return nullptr;
    //if there isn't a node to the left, return the current node
    else if (node->left == nullptr)
        return node;
    //else find the min of the left subtree
    else 
        return find_min(node->left);
}

int BinarySearchTree::find_max() const {
    if (root == nullptr) return numeric_limits<int>::max(); // INT_MAX

    return find_max(root)->data;
}
//find_max
//Purpose: Finds the maximum value in the tree
//Parameters: A node to start from
//Returns: A pointer to the node containing the max value
BinarySearchTree::Node *BinarySearchTree::find_max(Node *node) const {
    //if the node is null, return null
    if (node == nullptr) {
        return nullptr;
    }
    //if there isn't a node to the right, return the current node
    else if (node->right == nullptr)
        return node;
    //else find the max of the right subtree
    else 
        return find_max(node->right);
}

bool BinarySearchTree::contains(int value) const {
    if (contains(root, value))
        return true;
    else return false;

}

//contains
//Purpose: Checks if the tree rooted at a given node contains a given value
//Parameters: A root node and a value to search for
//Returns: True if the tree contains the value, false otherwise
bool BinarySearchTree::contains(Node *node, int value) const {
    //if the tree is empty, return false
    if (node == nullptr)
        return false;
    //base case: the value is located in the node
    else if (node->data == value)
        return true;
    //recursive case 1: the value is less than the current node
    else if (value < node->data)
        return contains(node->left, value);
    //recursive case 2: the value is greater than the current node
    else
        return contains(node->right, value);
}

void BinarySearchTree::insert(int value) {
    insert(root, nullptr, value);

}

//insert
//Purpose: Inserts a node containing a given value into the tree/
//Parameters: A node to compare the value against, its parent, and a value to insert.
//Returns: Void - inserts a node in the current instance at it's proper location.
//INVARIANT: NO NODE HAS MORE THAN 2 CHILDREN
//INVARIANT: ALL VALUES IN THE LEFT SUBTREE ARE LESS THAN THE PARENT
//INVARIANT: ALL VALUES IN THE RIGHT SUBTREE ARE GREATER THAN THE PARENT
void BinarySearchTree::insert(Node *node, Node *parent, int value) {
    //insert on an empty tree
    if(root == nullptr) {
        //instantiate a new node and set root to point to it
        root = newNode(value);
    }
    //else if the value is found, increase the count at that node
    else if (value == node->data) {
        node->count++;
    }
    //else if the value is less than the node
    else if (value < node->data) {
        //if the left node is null, set it to point to the new node
        if (node->left == nullptr)
            node->left = newNode(value);
        //else insert in the left tree
        else insert(node->left, node, value);
    }
    //else the value is greater than the node, insert in the right tree
    else {
        //if the right node is null, set it to point to the new node
        if (node->right == nullptr)
            node->right = newNode(value);
        //else insert in the right tree
        else insert(node->right, node, value);
    }
}

bool BinarySearchTree::remove(int value) {

    //
    return remove(root, nullptr, value);
    //
    // return remove(root, &root, value);
}

//remove
//Purpose: Removes a node from the tree.
//Parameters: The node to remove, its parent, and the value to remove. 
//Returns: True if the value was removed from the tree, false otherwise.
//         Updates current tree structure to replace value with the smallest
//         value in the right subtree.
bool BinarySearchTree::remove(Node *node, Node *parent, int value) {
    //Base case: the tree doesnt have the value - return false
    if (node == nullptr)
        return false;
    //recursive case 1: the value is less than the current node
    //remove from the left subtree
    if (value < node->data)
        return remove(node->left, node, value);
    //recursive case 2: the value is greater than the current node
    //remove from the right subtree
    else if (value > node->data)
        return remove(node->right, node, value);
    //else the node contains the value
    else {
        //if the count is > 1, subtract 1
        if (node->count > 1)
            node->count--;
        //otherwise the node needs to be removed from the tree
        else {
            //Case 1: the node is a leaf
            if (isLeaf(node)) {
                //if the node isn't the root of the tree
                if (node != root) {
                    //set parent's left or right to nullptr
                    if(parent->left == node)
                        parent->left = nullptr;
                    else 
                        parent->right = nullptr;
                }
                //else the node was the root, update root to nullptr
                else root = nullptr;
                //free memory associated with node
                delete node;
            }
            //case 2: node has a left child but no right child
            else if (node->left != nullptr && node->right == nullptr) {
                //if the node isn't the root of the tree
                if (node != root) {
                    //set parent's left or right to nullptr
                    if (parent->left == node) 
                        parent->left = node->left;
                    else
                        parent->right = node->left;
                }
                //else the node was the root, update root to the left node
                else root = node->left;
                //free memory associated with node
                delete node;
            }
            //case 3: node has a right child but not a left
            else if (node->left == nullptr && node->right != nullptr) {
                //if the node isn't the root
                if (node != root) {
                    //set parent's left or right to nullptr
                    if (parent->left == node) 
                        parent->left = node->right;
                    else
                        parent->right = node->right;
                }
                //else the node was the root, update root to the right node
                else root = node->right;
                //free memory associated with node
                delete node;
            }
            //case 4: node has a left and a right child
            else {
                //The node to delete will be the minimum value in the 
                //right subtree
                Node* nodeToDelete = find_min(node->right);
                //the parent of the node to delete
                Node *nodeParent = find_parent(node, nodeToDelete);
                //copy the data from the node to delete to the node to replace
                node->data = nodeToDelete->data;
                //if the deleted node was its parent's left child, set parent
                //left to nullptr
                if (nodeParent->left == nodeToDelete)
                    nodeParent->left = nullptr;
                //else the node was the parent's right child
                else
                    nodeParent->right = nullptr;
                //free memory associated with nodeToDelete
                delete nodeToDelete;
            }
        }
        //return true, a value was removed
        return true;
    }
}

// bool BinarySearchTree::remove(Node *node, Node **ptr_to_ptr_to_me, int value)
// {
//         // TODO:  Students write code here
// }

int BinarySearchTree::tree_height() const {
    return tree_height(root);
}

//treeHeight
//Purpose: Returns the height of a given node
//Parameters: The node whose height we wish to find
//Returns: An int, the height of the node.
int BinarySearchTree::tree_height(Node *node) const {
    if (node == nullptr)
        return -1;
    return 1 + max(tree_height(node->left), tree_height(node->right));
}

// returns the total number of nodes
int BinarySearchTree::node_count() const {
    return node_count(root);
}

//node_count
//Purpose: Counts the total number of nodes in the tree
//Parameters: A pointer to the root node
//Returns: An int, the number of nodes in the tree
int BinarySearchTree::node_count(Node *node) const {
    //Base case: node is null
    if(node == nullptr) {
        return 0;
    }
    //otherwise return 1 plus the count of the left and right subtrees
    return 1 + node_count(node->left) + node_count(node->right);
}

// return the sum of all the node values (including duplicates)
int BinarySearchTree::count_total() const {
    return count_total(root);
}

//count_total
//Purpose: Counts the total number of values in the tree, duplicates included
//Parameters: A pointer to the root node
//Returns: An int, the sum of the count of each node.
int BinarySearchTree::count_total(Node *node) const {
    //Base case: node is null
    if(node == nullptr) {
        return 0;
    }
    //otherwise return the count of the current node plus the count of 
    //the left and right subtrees
    return node->count + count_total(node->left) + count_total(node->right);
}

BinarySearchTree::Node *BinarySearchTree::find_parent(Node *node,
                                                      Node *child) const {
    if (node == nullptr) return nullptr;

    // if either the left or right is equal to the child,
    // we have found the parent
    if (node->left == child or node->right == child) { return node; }

    // Use the binary search tree invariant to walk the tree
    if (child->data > node->data) {
        return find_parent(node->right, child);
    } else {
        return find_parent(node->left, child);
    }
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const {
    size_t      numLayers  = tree_height() + 1;
    size_t      levelWidth = 4;
    const char *rootPrefix = "-> ";

    // Need numLayers * levelWidth characters for each layer of tree.
    // Add an extra levelWidth characters at front to avoid if statement
    // 1 extra char for nul character at end
    char *start = new char[(numLayers + 1) * levelWidth + 1];

    print_tree(root, start + levelWidth, start + levelWidth, rootPrefix);
    delete[] start;
}

// Logic and Output Reference:
// https://www.techiedelight.com/c-program-print-binary-tree/
void BinarySearchTree::print_tree(Node *node, char *const currPos,
                                  const char *const fullLine,
                                  const char *const branch) const {
    if (node == nullptr) return;

    // 4 characters + 1 for nul terminator
    using TreeLevel                    = char[5];
    static const int       levelLength = sizeof(TreeLevel) - 1;
    static const TreeLevel UP = ".-- ", DOWN = "`-- ", EMPTY = "    ",
                           CONNECT = "   |";
    // Copies prev into dest and advances dest by strlen(prev)
    auto set = [](char *dest, const char *prev) {
        size_t p = strlen(prev);
        return (char *)memcpy(dest, prev, p) + p;
    };

    print_tree(node->right, set(currPos, EMPTY), fullLine, UP);

    // Clear any characters that would immediate precede the "branch"
    // Don't need to check for root (i.e start of array),fullLine is padded
    set(currPos - levelLength, EMPTY);

    // Terminate fullLine at current level
    *currPos = '\0';

    std::cerr << fullLine << branch << node->data
              << (node->count > 1 ? "*" : "") << endl;

    // Connect upper branch to parent
    if (branch == UP) set(currPos - levelLength, CONNECT);

    // Connect lower branch to parent
    print_tree(node->left, set(currPos, CONNECT), fullLine, DOWN);
}

//isLeaf
//Purpose: Checks if the current node is a leaf (has no children)
//Parameters: A pointer to the node to test.
//Returns: True if the node is a leaf, false otherwise.
bool BinarySearchTree::isLeaf(Node *node) const {
    //if both left and right pointers are nullptr, return true
    if (node->left == nullptr &&
        node->right == nullptr)
        return true;
    //otherwise the node has a child
    else return false;
}

//newNode
//Purpose: Instantiates a new Node of count 1 and null child pointers.
//Parameters: A value to put in the node.
//Returns: A pointer to the new Node.
BinarySearchTree::Node *BinarySearchTree::newNode(int value) {
    //allocate memory for a new node
    Node *node = new Node;
    //set the count to 1
    node->count = 1;
    //set the data equal to the input value
    node->data = value;
    //set the child pointers to nullptr;
    node->left = nullptr;
    node->right = nullptr;
    //return a pointer to the node
    return node;
}

