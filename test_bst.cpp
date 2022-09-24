#include "bst.h"

int main(void){
    BST<int> test_tree;
    test_tree.add(8);
    test_tree.add(10);
    test_tree.add(3);
    test_tree.add(1);
    test_tree.add(5);
    test_tree.print();
    return 0;

}
