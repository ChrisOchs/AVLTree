#include <iostream>

#include "AVLTree.h"

int main() {

    AVLTree<int> avlTree;

    avlTree.insert(10);
    avlTree.insert(5);
    avlTree.insert(15);
    avlTree.insert(1);
    avlTree.insert(0);
    avlTree.insert(2);
    avlTree.insert(3);

    avlTree.print();

    std::cout<<std::endl;
    std::cout<<std::endl;

    avlTree.remove(0);

    avlTree.print();

    std::cout<<std::endl;
    std::cout<<std::endl;

    avlTree.remove(1);

    avlTree.print();


    return 0;
}
