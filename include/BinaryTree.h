#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#include <stack>
#include <queue>

#include "BTNode.h"
#include "BinaryTreeVisitor.h"

template<class ELEM_T, class NODE_T>
class BinaryTree {
    private:

    protected:
        NODE_T* root;

        void rotateRight(NODE_T*);
        void rotateLeft(NODE_T*);

    public:
    BinaryTree();
        ~BinaryTree();

        bool isRoot(NODE_T*) const;
        bool isInternal(NODE_T*) const;
        bool isExternal(NODE_T*) const;

        NODE_T* getRoot() const;

        void binaryPreorder(BinaryTreeVisitor<NODE_T>*) const;
        void binaryInorder(BinaryTreeVisitor<NODE_T>*) const;
        void binaryPostorder(BinaryTreeVisitor<NODE_T>*) const;

        bool equals(BinaryTree*) const;

        virtual int getHeight() const;

        void print() const;
};

template<class ELEM_T, class NODE_T>
BinaryTree<ELEM_T, NODE_T>::BinaryTree() {
    this->root = NULLPTR;
}

template<class ELEM_T, class NODE_T>
BinaryTree<ELEM_T, NODE_T>::~BinaryTree() {

}

template<class ELEM_T, class NODE_T>
bool BinaryTree<ELEM_T, NODE_T>::isRoot(NODE_T* node) const {
    return (node != NULLPTR && node == this->root);
}

template<class ELEM_T, class NODE_T>
bool BinaryTree<ELEM_T, NODE_T>::isInternal(NODE_T* node) const {
    return (node != NULLPTR && node->getLeftChild() != NULLPTR && node->getRightChild() != NULLPTR);
}

template<class ELEM_T, class NODE_T>
bool BinaryTree<ELEM_T, NODE_T>::isExternal(NODE_T* node) const {
    return (node != NULLPTR && node->getLeftChild() == NULLPTR && node->getRightChild() == NULLPTR);
}

template<class ELEM_T, class NODE_T>
NODE_T* BinaryTree<ELEM_T, NODE_T>::getRoot() const {
    return this->root;
}

template<class ELEM_T, class NODE_T>
int BinaryTree<ELEM_T, NODE_T>::getHeight() const {
    if(this->getRoot() == NULLPTR) {
        return -1;
    }

    int height = 0;

    std::queue<NODE_T*> nodeQueue;
    nodeQueue.push(this->getRoot());

    while(!nodeQueue.empty()) {
        height++;

        int levelCount = nodeQueue.size();

        while(levelCount > 0) {
            NODE_T* node = nodeQueue.front();
            nodeQueue.pop();

            if(this->isInternal(node)) {
                nodeQueue.push(node->getLeftChild());
                nodeQueue.push(node->getRightChild());
            }

            levelCount--;
        }
    }

    return height - 1;
}

template<class ELEM_T, class NODE_T>
void BinaryTree<ELEM_T, NODE_T>::rotateRight(NODE_T* node) {
    NODE_T* parent = node->getParent();
    NODE_T* p = node->getLeftChild();

    node->setLeftChild(p->getRightChild());
    p->setRightChild(node);

    p->setParent(parent);

    if(node == this->root) {
        this->root = p;
    }
}

template<class ELEM_T, class NODE_T>
void BinaryTree<ELEM_T, NODE_T>::rotateLeft(NODE_T* node) {
    NODE_T* parent = node->getParent();
    NODE_T* q = node->getRightChild();

    node->setRightChild(q->getLeftChild());
    q->setLeftChild(node);

    q->setParent(parent);

    if(node == this->root) {
        this->root = q;
    }
}

template<class ELEM_T, class NODE_T>
void BinaryTree<ELEM_T, NODE_T>::binaryPreorder(BinaryTreeVisitor<NODE_T>* visitor) const {

    if(this->root == NULLPTR) {
        return;
    }

    std::stack<NODE_T*> stk;

    stk.push(this->root);

    while(!stk.empty()) {
        NODE_T* ptr = stk.top();
        stk.pop();

        visitor->visit(ptr);

        if(this->isInternal(ptr)) {
            stk.push(ptr->getRightChild());
            stk.push(ptr->getLeftChild());
        }
    }
}

template<class ELEM_T, class NODE_T>
void BinaryTree<ELEM_T, NODE_T>::binaryPostorder(BinaryTreeVisitor<NODE_T>* visitor) const {

}

template<class ELEM_T, class NODE_T>
void BinaryTree<ELEM_T, NODE_T>::print() const {

    if(this->root == NULLPTR) {
        return;
    }

    std::queue<NODE_T*> nodeQueue;
    std::queue<int> indexQueue;

    nodeQueue.push(this->root);
    indexQueue.push(1);

    int startIndex = 0;
    int endIndex = 0;

    int level = 0;

    int maxNodesInLevel = 0;

    int lastIndex = 0;

    int levelNodeSpacing = 0;

    int initialOffset = 0;

    int height = this->getHeight();

    while(!nodeQueue.empty()) {
        NODE_T* node = nodeQueue.front();
        int index = indexQueue.front();

        nodeQueue.pop();
        indexQueue.pop();

        if(index > endIndex) {
            startIndex = (1 << level);
            endIndex = (startIndex * 2) - 1;

            maxNodesInLevel = startIndex;

            lastIndex = startIndex;

            initialOffset = (1 << (height - level)) - 1;
            levelNodeSpacing = (1 << (height - level + 1));

            std::cout<<std::endl;

            for(int c = 1; c <= initialOffset; c++) {
                std::cout<<" ";
            }

            level++;
        }

        if(index > lastIndex + 1) {

            int numTimes;

            if(lastIndex == startIndex) {
                numTimes = index + 1;
            } else {
                numTimes = index - 1;
            }

            for(int fillerIdx = lastIndex; fillerIdx < numTimes; fillerIdx++) {
                for(int c = 1; c <= levelNodeSpacing; c++) {
                    std::cout<<" ";
                }
            }
        }

        if(this->isExternal(node)) {
            std::cout<<"X";
        } else {
            std::cout<<node->getElement();

            nodeQueue.push(node->getLeftChild());
            nodeQueue.push(node->getRightChild());

            indexQueue.push(2 * index);
            indexQueue.push(2 * index + 1);
        }

        if(index < endIndex) {
            for(int c = 1; c <= levelNodeSpacing; c++) {
                std::cout<<" ";
            }
        }

        lastIndex = index;
    }
}

template<class ELEM_T, class NODE_T>
bool BinaryTree<ELEM_T, NODE_T>::equals(BinaryTree* other) const {
    return false;
}

#endif // BINARYTREE_H_INCLUDED
