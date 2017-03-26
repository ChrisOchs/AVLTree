#ifndef BTNODE_H_INCLUDED
#define BTNODE_H_INCLUDED

#define NULLPTR 0

template<class ELEM_T, class NODE_T>
class BTNode {
    private:
        ELEM_T element;

        NODE_T* parent;
        NODE_T* leftChild;
        NODE_T* rightChild;

    public:
        BTNode();
        virtual ~BTNode();

        NODE_T* getParent() const;
        NODE_T* getLeftChild() const;
        NODE_T* getRightChild() const;

        ELEM_T getElement() const;

        void setParent(NODE_T*);
        void setLeftChild(NODE_T*);
        void setRightChild(NODE_T*);

        void setElement(ELEM_T);
};

template<class ELEM_T, class NODE_T>
BTNode<ELEM_T, NODE_T>::BTNode() {
    this->parent = NULLPTR;
    this->leftChild = NULLPTR;
    this->rightChild = NULLPTR;
}

template<class ELEM_T, class NODE_T>
BTNode<ELEM_T, NODE_T>::~BTNode() {

}

template<class ELEM_T, class NODE_T>
NODE_T* BTNode<ELEM_T, NODE_T>::getParent() const {
    return this->parent;
}

template<class ELEM_T, class NODE_T>
NODE_T* BTNode<ELEM_T, NODE_T>::getLeftChild() const {
    return this->leftChild;
}

template<class ELEM_T, class NODE_T>
NODE_T* BTNode<ELEM_T, NODE_T>::getRightChild() const {
    return this->rightChild;
}

template<class ELEM_T, class NODE_T>
ELEM_T BTNode<ELEM_T, NODE_T>::getElement() const {
    return this->element;
}

template<class ELEM_T, class NODE_T>
void BTNode<ELEM_T, NODE_T>::setParent(NODE_T* parent)  {
    this->parent = parent;
}

template<class ELEM_T, class NODE_T>
void BTNode<ELEM_T, NODE_T>::setLeftChild(NODE_T* leftChild) {
    this->leftChild = leftChild;

    if(leftChild != NULLPTR) {
        this->leftChild->setParent(dynamic_cast<NODE_T*>(this));
    }
}

template<class ELEM_T, class NODE_T>
void BTNode<ELEM_T, NODE_T>::setRightChild(NODE_T* rightChild) {
    this->rightChild = rightChild;

    if(rightChild != NULLPTR) {
        this->rightChild->setParent(dynamic_cast<NODE_T*>(this));
    }
}

template<class ELEM_T, class NODE_T>
void BTNode<ELEM_T, NODE_T>::setElement(ELEM_T element) {
    this->element = element;
}

#endif // BTNODE_H_INCLUDED
