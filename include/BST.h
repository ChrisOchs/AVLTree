#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include "BTNode.h"
#include "BinaryTree.h"

#define NO_SUCH_KEY NULLPTR

template<class ELEM_T, class NODE_T>
class BST : public BinaryTree<ELEM_T, NODE_T> {

    private:
        NODE_T* searchForLocation(ELEM_T) const;

        virtual NODE_T* makeNode() = 0;

    public:
        BST();
        ~BST();

        NODE_T* search(ELEM_T) const;

        virtual NODE_T* insert(ELEM_T);
        virtual void remove(ELEM_T);

        NODE_T* inorderPredecessor(NODE_T*) const;
        NODE_T* inorderSuccessor(NODE_T*) const;
};

template<class ELEM_T, class NODE_T>
BST<ELEM_T, NODE_T>::BST() {

}

template<class ELEM_T, class NODE_T>
BST<ELEM_T, NODE_T>::~BST() {

}

template<class ELEM_T, class NODE_T>
NODE_T* BST<ELEM_T, NODE_T>::search(ELEM_T element) const {

    NODE_T* node = this->searchForLocation(element);

    if(node == NULLPTR || this->isExternal(node)) {
        return NO_SUCH_KEY;
    } else {
        return node;
    }
}

template<class ELEM_T, class NODE_T>
NODE_T* BST<ELEM_T, NODE_T>::searchForLocation(ELEM_T element) const {

    if(this->root == NULLPTR) {
        return NULLPTR;
    }

    NODE_T* ptr = this->root;

    while(this->isInternal(ptr)) {

        if(ptr->getElement() == element) {
            return ptr;
        }

        if(element < ptr->getElement()) {
            ptr = ptr->getLeftChild();
        } else {
            ptr = ptr->getRightChild();
        }
    }

    return ptr;
}

template<class ELEM_T, class NODE_T>
NODE_T* BST<ELEM_T, NODE_T>::insert(ELEM_T element) {

    if(this->root == NULLPTR) {
        NODE_T* node = this->makeNode();
        node->setElement(element);

        node->setLeftChild(this->makeNode());
        node->setRightChild(this->makeNode());

        this->root = node;

        return this->root;
    }

    NODE_T* position = this->searchForLocation(element);

    if(this->isInternal(position)) {
        return position;
    }

    position->setElement(element);

    position->setLeftChild(this->makeNode());
    position->setRightChild(this->makeNode());

    return position;
}

template<class ELEM_T, class NODE_T>
void BST<ELEM_T, NODE_T>::remove(ELEM_T element) {

    NODE_T* removePoint = this->search(element);

    if(removePoint == NO_SUCH_KEY) {
        return;
    }

    if(this->isExternal(removePoint->getLeftChild()) && this->isExternal(removePoint->getRightChild())) {
        delete removePoint->getLeftChild();
        delete removePoint->getRightChild();

        if(removePoint == this->getRoot()) {
            delete removePoint;

            this->root = NULLPTR;
        } else {
            removePoint->setLeftChild(NULLPTR);
            removePoint->setRightChild(NULLPTR);
        }

        return;
    }

    if(this->isExternal(removePoint->getLeftChild())) {
        NODE_T* rightChild = removePoint->getRightChild();

        if(removePoint == this->getRoot()) {
            rightChild->setParent(NULLPTR);

            this->root = rightChild;

        } else {
            NODE_T* parent = removePoint->getParent();
            parent->setLeftChild(rightChild);
        }

        delete removePoint->getLeftChild();
        delete removePoint;

        return;
    }

    if(this->isExternal(removePoint->getRightChild())) {
        NODE_T* leftChild = removePoint->getLeftChild();

        if(removePoint == this->getRoot()) {
            leftChild->setParent(NULLPTR);

            this->root = leftChild;

        } else {
            NODE_T* parent = removePoint->getParent();
            parent->setRightChild(leftChild);
        }

        delete removePoint->getRightChild();
        delete removePoint;

        return;
    }
}

template<class ELEM_T, class NODE_T>
NODE_T* BST<ELEM_T, NODE_T>::inorderSuccessor(NODE_T* node) const {

    NODE_T* rc = node->getRightChild();

    if(this->isExternal(rc)) {
        NODE_T* parent = node->getParent();
        NODE_T* x = node;

        while(parent != NULLPTR && x == parent->getRightChild()) {
            x = parent;
            parent = parent->getParent();
        }

        if(parent == NULLPTR) {
            return NO_SUCH_KEY;
        } else {
            return parent;
        }
    } else {
        NODE_T* ptr = rc;

        while(!this->isExternal(ptr->getLeftChild())) {
            ptr = ptr->getLeftChild();
        }

        return ptr;
    }
}

template<class ELEM_T, class NODE_T>
NODE_T* BST<ELEM_T, NODE_T>::inorderPredecessor(NODE_T* node) const {

    NODE_T* lc = node->getLeftChild();

    if(this->isExternal(lc)) {
        NODE_T* parent = node->getParent();
        NODE_T* x = node;

        while(parent != NULLPTR && x == parent->getLeftChild()) {
            x = parent;
            parent = parent->getParent();
        }

        if(parent == NULLPTR) {
            return NO_SUCH_KEY;
        } else {
            return parent;
        }
    } else {
        NODE_T* ptr = lc;

        while(!this->isExternal(ptr->getRightChild())) {
            ptr = ptr->getRightChild();
        }

        return ptr;
    }
}

#endif // BST_H_INCLUDED
