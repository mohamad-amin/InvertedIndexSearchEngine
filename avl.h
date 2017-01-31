#ifndef AVL_H
#define AVL_H

#include "linkedlist.h"
#include "customfile.h"
#include "stack.h"

template <class T> struct AVLNode {

    LinkedList<CustomFile*>* list;

    T data;
    AVLNode<T> *leftChild;
    AVLNode<T> *rightChild;
    int leftHeight, rightHeight;

    AVLNode(T data) : data(data) {
        list = new LinkedList<CustomFile*>;
        leftHeight = rightHeight = 0;
        leftChild = rightChild = 0;
    }

    AVLNode(T data, AVLNode<T> *leftChild, AVLNode<T> *rightChild) {
        list = new LinkedList<CustomFile*>;
        this->data = data;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
        leftHeight = rightHeight = 0;
    }

    AVLNode() {
        list = new LinkedList<CustomFile*>;
        leftHeight = rightHeight = 0;
        leftChild = rightChild = 0;
    }

};

template <typename T>
struct ParentChildWay {

    AVLNode<T> *parent;
    AVLNode<T> *child;
    bool isLeft;

    ParentChildWay(AVLNode<T> *parent, AVLNode<T> *child, bool isLeft) : parent(parent), child(child), isLeft(isLeft){}

    ParentChildWay(AVLNode<T>* child) : child(child) {
        isLeft = true;
        parent = 0;
    }

};

template <class T>
class AVL {

public:
    AVL();
    AVLNode<T>* get(T);
    int getHeight();
    int getSize();
    AVLNode<T>* add(T);
    bool clear();
    AVLNode<T>* remove(T);
    LinkedList<AVLNode<T>>* getNodesInInorder();

private:
    AVLNode<T> *root;
    AVLNode<T> *getNode(AVLNode<T> *root, T);
    void getInorder(LinkedList<AVLNode<T>>*, AVLNode<T>*);
    void getLevelOrder(Stack<ParentChildWay<T>*>*, AVLNode<T>*);
    void rotateRR(AVLNode<T>*, AVLNode<T>*, bool);
    void rotateRL(AVLNode<T>*, AVLNode<T>*, bool);
    void rotateLL(AVLNode<T>*, AVLNode<T>*, bool);
    void rotateLR(AVLNode<T>*, AVLNode<T>*, bool);
    void fixNode(AVLNode<T>*, AVLNode<T>*, bool);
    void recalculateHeight(AVLNode<T>*);
    int getMaxNodeHeight(AVLNode<T>*);
    int getHeightHelper(AVLNode<T>*);
    void refixTree(AVLNode<T>*);

};

#include "avl.hpp"

#endif // AVL_H
