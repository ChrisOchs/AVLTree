#ifndef AVLTREENODE_H
#define AVLTREENODE_H

#include "BTNode.h"

template<class T>
class AVLTreeNode: public BTNode< T, AVLTreeNode<T> >
{
    private:
        int subtreeHeight;

    public:
        AVLTreeNode();
        virtual ~AVLTreeNode();

        int getSubtreeHeight() const;
        void setSubtreeHeight(int);
};

template<class T>
AVLTreeNode<T>::AVLTreeNode() {
    this->subtreeHeight = 0;
}

template<class T>
AVLTreeNode<T>::~AVLTreeNode() {

}

template<class T>
int AVLTreeNode<T>::getSubtreeHeight() const {
    return this->subtreeHeight;
}

template<class T>
void AVLTreeNode<T>::setSubtreeHeight(int height) {
    this->subtreeHeight = height;
}


#endif // AVLTREENODE_H
