#ifndef BST_H
#define BST_H

#include "linkedlist.h"
#include "customfile.h"

template <class T> struct TreeNode {

    LinkedList<CustomFile*>* list;

    T data;
    TreeNode<T> *leftChild;
    TreeNode<T> *rightChild;

    TreeNode(T data) : data(data) {
        list = new LinkedList<CustomFile*>;
    }

    TreeNode(T data, TreeNode<T> *leftChild, TreeNode<T> *rightChild) {
        list = new LinkedList<CustomFile*>;
        this->data = data;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
    }

    TreeNode() {
        list = new LinkedList<CustomFile*>;
    }

};

template <class T>
class BST {

public:
    BST();
    TreeNode<T>* get(T);
    int getHeight();
    int getSize();
    TreeNode<T>* add(T);
    bool clear();
    TreeNode<T>* remove(T);
    LinkedList<TreeNode<T>>* getNodesInInorder();

private:
    TreeNode<T> *root;
    TreeNode<T> *getNode(TreeNode<T> *root, T);
    void getInorder(LinkedList<TreeNode<T>> *list, TreeNode<T> *root);

};

#include "bst.hpp"

#endif // BST_H
