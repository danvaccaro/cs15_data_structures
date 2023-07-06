/*
 * Filename: AVLTree.cpp
 * Contains: Implementation of AVL Trees for COMP15
 * Part of: Lab assignment "AVL Trees" for Comp 15
 *
 */

#include <iostream>
#include "AVLTree.h"

using namespace std;


/* 
 * Input: data (the value to store), height of the node, left and 
 *       right child pointers
 * Returns: avl tree node.
 * Does: creates a new node with values given as input parameter
 */
static Node *newNode(int data, int height, Node *left, Node *right)
{
        Node *np = new Node();
    
        np->data  = data;
        np->height = height;
        np->left  = left;
        np->right = right;

        return np;
} 


/* 
 * Input: data (the value to store)
 * Returns: avl tree node.
 * Does: calls a helper function to create a new nodewith default
 *        values parameter
 */
static Node *newNode(int data)
{
        return newNode(data, 0, nullptr, nullptr);
}



/* 
 * Input: the node to be deleted.
 * Returns: N/A
 * Does: Set node contents to predictable, "deleted" node values
 *       and then recycle the node.
 */
static void deleteNode(Node *np)
{
        np->height = -1;  /* Something that couldn't be in a real node */
        np->data  = -1;   /* Arbitrary value                           */
        np->left  = np->right = nullptr;
        delete 
        np;
}



/* 
 * Input: N/A
 * Returns: AVL class object
 * Does: Sets the root node to nullptr
 */
AVLTree::AVLTree()
{
        root = nullptr;
}

/* 
 * Input: N/A
 * Returns: N/A
 * Does: Deletes the AVL tree clears the memory used. Resets the root pointer
 */
AVLTree::~AVLTree()
{
        /* walk tree in post-order traversal and delete */
        post_order_delete(root);
        root = nullptr;  /* not really necessary, since the tree is going
                            away, but might want to guard against someone
                            using a pointer after deleting */
}


/* 
 * Input: a node of an AVL tree
 * Returns: N/A
 * Does: Deletes the AVL tree of node in a post order manner.
 */
void AVLTree::post_order_delete(Node *node)
{
        if (node != nullptr) {
                post_order_delete(node->left);
                post_order_delete(node->right);
                deleteNode(node);
        }
}


/* 
 * Input: an integer value to be inserted in the AVL tree
 * Returns: N/A
 * Does: Calls a helper function to insert the given value in the tree.
 */
void AVLTree::insert(int value)
{
        root = insert(root, value);
}


/* 
 * Input: Node np - a node of the avl tree. value - an integer value to 
 *         be inserted in the AVL tree
 * Returns: the updated subtree of np.
 * Does: Inserts within a AVL tree the given value, while maintaining the 
 *        AVL invarient 
 */
Node *AVLTree::insert(Node *np, int value)
{
        /* BST insertion start */
        if (np == nullptr) {
                return newNode(value);

        } else if (value < np->data) {
                np->left = insert(np->left, value);
        
        } else if (value > np->data) {
                np->right = insert(np->right, value);
        } else if (value == np->data) {
                return np;
        }
        /* BST insertion ends */

        /* AVL maintenance start */
        np->height = 1 + max(nodeHeight(np->left), nodeHeight(np->right));
        np = balance (np);
        /* AVL maintenace end */

        return np;
}

/* 
 * Input: Node np - a node of the avl tree.
 * Returns: the balanced subtree of np.
 * Does: If unbalanced, balances the subtree of node.
 */
Node *AVLTree::balance(Node *np) 
{
        //only balance if height diff > |1|
        if(abs(heightDiff(np)) > 1 ) {
                //if the node is L
                if (np->left != nullptr) {
                        //if the node is LL
                        if (np->left->left != nullptr) {
                                std::cerr << "LL!\n";
                                return rightRotate(np);
                        }
                                
                        //else if the node is LR
                        else {
                                std::cerr << "LR!\n";
                              
                              leftRotate(np->left);
                              return rightRotate(np);
                        }
                }
                        
                //if the node is R
                else if (np->right != nullptr) {
                        //if the node is RR
                        if (np->right->right != nullptr) {
                                std::cerr << "RR!\n";
                                return leftRotate(np);
                        }
                        
                        //else if the node is RL
                        else {
                                std::cerr << "RL!";
                                rightRotate(np->right);
                                return leftRotate(np);
                        }
                                
                }
        }
        return np;
}

/* 
 * Input: Node np - a node of the avl tree.
 * Returns: newly rooted node.
 * Does: left rotate subtree rooted with np  
 */
Node *AVLTree::rightRotate(Node *np) 
{
        std::cerr << "right rotate\n";
        Node* newRoot = np->left;
        np->left = newRoot->right;
        newRoot->right = np;
        newRoot->height = 1 + max(nodeHeight(newRoot->left), nodeHeight(newRoot->right));
        np->height = 1 + max(nodeHeight(np->left), nodeHeight(np->right));

        root = newRoot;
        return newRoot;
} 
  
/* 
 * Input: Node np - a node of the avl tree.
 * Returns: newly rooted node.
 * Does: left rotate subtree rooted with np  
 */
Node *AVLTree::leftRotate(Node *np) 
{ 
        std::cerr << "left rotate\n";
        Node* newRoot = np->right;
        np->right = newRoot->left;
        newRoot->left = np;
        newRoot->height = 1 + max(nodeHeight(newRoot->left), nodeHeight(newRoot->right));
        np->height = 1 + max(nodeHeight(np->left), nodeHeight(np->right));

        root = newRoot;
        return newRoot;
} 



/* 
 * Input: Node np - a node of the avl tree.
 * Returns: integer value signifying the height difference.
 * Does: calculates the difference in the height of the left and child 
 *       subtree of np
 */
int AVLTree::heightDiff(Node *np)
{
        int l_height = nodeHeight (np->left);
        int r_height = nodeHeight (np->right);

        int b_factor= l_height - r_height;
        return b_factor;
}



/* 
 * Input: Node np - a node of the avl tree.
 * Returns: integer denoting the height attribute
 * Does: a getter to get the value of the height attribute.
 */
int AVLTree::nodeHeight(Node *node) 
{ 
        if (node == nullptr) 
                return -1; 
        return node->height; 
} 


/* 
 * Input: value to be removed from the avl tree
 * Returns: bool signifying the success of the function.
 * Does: removes the given node value form the avl tree
 *       with the help of a helper function.
 */
bool AVLTree::remove(int value)
{
        return remove(root, value);
}

/* 
 * Input: Node np - a node of the avl tree. value to be removed 
 * from the avl tree
 * Returns: bool signifying the success of the function.
 * Does: removes the given node value form the avl tree
 */
bool AVLTree::remove(Node *node, int value)
{
        /* BONUS TODO: Students write code here */
}


/* 
 * Input: N/A
 * Returns: N/A
 * Does: uses a helper function to print a pretty tree.
 */
void AVLTree::print_tree() const
{
        printPretty(root, 1, 0, std::cout);
}
