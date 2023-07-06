#ifndef BSTREE_H
#define BSTREE_H
/*
 * Class for a binary search tree (BST) with integer keys
 * for Data Structures (BST) lab
 */


class BST {
public:
    BST();
    ~BST();

    void unbalancedInsert(int v);
    void inOrder();
    void preOrder();
    void postOrderDelete();
    void levelOrder();

private:
    struct BSTNode {
        int      value;
        BSTNode *left;
        BSTNode *right;
    };
    BSTNode *root;

    BSTNode *newBSTNode(int v);
    BSTNode *newBSTNode(int v, BSTNode *left, BSTNode *right);

    bool     isEmpty(BSTNode *root);
    BSTNode *unbalancedInsert(BSTNode *root, int v);
    void     inOrder(BSTNode *root);
    void     preOrder(BSTNode *root);
    void     levelOrder(BSTNode *root);
    void     postOrderDelete(BSTNode *root);
};

#endif
