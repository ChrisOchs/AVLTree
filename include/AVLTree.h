#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <queue>

#include "BST.h"
#include "AVLTreeNode.h"

template<class T>
class AVLTree : public BST<T, AVLTreeNode<T> > {

    private:
        virtual AVLTreeNode<T>* makeNode();

        void updateFrom(AVLTreeNode<T>*);

    public:
        AVLTree();
        ~AVLTree();

        virtual int getHeight() const;

        virtual AVLTreeNode<T>* insert(T);
        virtual void remove(T);
};

template<class T>
AVLTree<T>::AVLTree() {

}

template<class T>
AVLTree<T>::~AVLTree() {

}

template<class T>
AVLTreeNode<T>* AVLTree<T>::makeNode() {
    return new AVLTreeNode<T>();
}

template<class T>
int AVLTree<T>::getHeight() const {
    if(this->getRoot() == NULLPTR) {
        return -1;
    }

    return this->getRoot()->getSubtreeHeight();
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::insert(T element) {
    AVLTreeNode<T>* insertedLocation = BST<T, AVLTreeNode<T> >::insert(element);

    if(insertedLocation == this->root) {
        insertedLocation->setSubtreeHeight(1);
    }

    updateFrom(insertedLocation);

    return insertedLocation;
}

template<class T>
void AVLTree<T>::remove(T element) {

    BST<T, AVLTreeNode<T> >::remove(element);

    // TODO: Update, restructure
}

template<class T>
void AVLTree<T>::updateFrom(AVLTreeNode<T>* node) {
    AVLTreeNode<T>* ptr = node;

    while(ptr != NULLPTR) {
        int leftHeight = ptr->getLeftChild()->getSubtreeHeight();
        int rightHeight = ptr->getRightChild()->getSubtreeHeight();
        int diff = leftHeight - rightHeight;

        if(abs(diff) > 1) {
            // TODO: do rotation(s)
        }

        ptr->setSubtreeHeight(std::max(leftHeight, rightHeight) + 1);

        ptr = ptr->getParent();
    }
}

#endif // AVLTREE_H_INCLUDED
