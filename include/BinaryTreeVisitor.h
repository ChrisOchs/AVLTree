#ifndef BINARYTREEVISITOR_H_INCLUDED
#define BINARYTREEVISITOR_H_INCLUDED

template<class NODE_T>
class BinaryTreeVisitor {

    public:
        virtual void visit(NODE_T*) = 0;

};

#endif
