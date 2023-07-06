#include "BinarySearchTree.h"
#include <iostream>

int main() {
    BinarySearchTree testBST_1;
    BinarySearchTree testBST_2;
    std::cout << testBST_1.isEmpty() << "\n";
    std::cout << "node count: " << testBST_1.node_count() << "\n";
    testBST_1.insert(45);
    testBST_1.insert(33);
    testBST_1.insert(22);
    testBST_1.insert(65);
    testBST_1.insert(70);
    testBST_1.insert(64);
    testBST_1.insert(44);
    
    testBST_1.print_tree();
    std::cout << "removing 45...\n";
    std::cout << testBST_1.remove(45) <<"\n";
    std::cout << "node count: " << testBST_1.node_count() << "\n";
    std::cout << "removing 65...\n";
    std::cout << testBST_1.remove(65) <<"\n";
    testBST_1.print_tree();
    std::cout << "node count: " << testBST_1.node_count() << "\n";
        std::cout << "removing 33...\n";
    std::cout << testBST_1.remove(33) <<"\n";
    testBST_1.print_tree();
    std::cout << "node count: " << testBST_1.node_count() << "\n";
            std::cout << "removing 45...\n";
    std::cout << testBST_1.remove(45) <<"\n";
    testBST_1.print_tree();
    testBST_1.insert(44);
    testBST_1.insert(44);
     testBST_1.print_tree();
    std::cout << "node count: " << testBST_1.node_count() << "\n";
    std::cout << "value count: " << testBST_1.count_total() << "\n";
    testBST_2 = testBST_1;
    testBST_2.print_tree();
    
    return 0;
}