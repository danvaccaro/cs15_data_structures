#include <iostream>

#include "BSTree.h"

using namespace std;

void buildTree(BST &t, int values[], int numValues) {
    for (int i = 0; i < numValues; ++i)
        t.unbalancedInsert(values[i]);
}

void testInOrder(BST &t) {
    cout << "Ricky to the rescue:" << endl;
    cout << "printing inorder: ";
    t.inOrder();
    cout << endl;
    cout << "Answer:           17 22 26 27 30 36 41 45 54 74 76 82";
    cout << endl;
}

void testPreOrder(BST &t) {
    cout << "Stacey saves the day" << endl;
    cout << "printing preorder: ";
    t.preOrder();
    cout << endl;
    cout << "Answer:            54 22 17 41 36 30 26 27 45 74 76 82";
    cout << endl;
}

// void testPostOrder(BST &t)
// {
//         cout << endl;
//         cout << "printing postorder: ";
//         t.postOrder();
//         cout << endl;
//         cout <<"Answer:             17 27 26 30 36 45 41 22 82 76 74 54  ";
//         cout << endl;
// }

void testLevelOrder(BST &t) {
    cout << "Quiet down, Quinn's in Town" << endl;
    cout << "printing levelorder: ";
    t.levelOrder();
    cout << endl;

    cout << "Answer:              54 22 74 17 41 76 36 45 82 30 26 27";
    cout << endl;
}

int main() {
    BST t;
    int testData[] = {54, 22, 17, 41, 36, 30, 74, 76, 26, 27, 45, 82};

    buildTree(t, testData, sizeof(testData) / sizeof(int));

    cout << endl;
    testInOrder(t);

    // cout << endl;
    // testPostOrder(t);

    cout << endl;
    testPreOrder(t);

    cout << endl;
    testLevelOrder(t);

    return 0;
}
