#ifndef AVLTST_H
#define AVLTST_H


#include "customfile.h"
#include "linkedlist.h"
#include "stack.h"

struct AVLTSTNode {

    LinkedList<CustomFile*> *list;
    std::string *word;

    char data;
    AVLTSTNode* leftChild;
    AVLTSTNode* rightChild;
    AVLTSTNode* middleChild;
    bool isEndOfWord;
    int leftHeight, rightHeight;

    AVLTSTNode(char data) : data(data) {
        this->leftChild = NULL;
        this->middleChild = NULL;
        this->rightChild = NULL;
        this->list = new LinkedList<CustomFile*>;
        leftHeight = rightHeight = 0;
    }

    AVLTSTNode(char data, AVLTSTNode* leftChild, AVLTSTNode* middleChild, AVLTSTNode* rightChild) {
        this->data = data;
        this->leftChild = leftChild;
        this->middleChild = middleChild;
        this->rightChild = rightChild;
        this->list = new LinkedList<CustomFile*>;
        this->isEndOfWord = false;
        leftHeight = rightHeight = 0;
    }

    AVLTSTNode() {
        this->list = new LinkedList<CustomFile*>;
        leftChild = NULL;
        middleChild = NULL;
        rightChild = NULL;
        this->isEndOfWord = false;
        leftHeight = rightHeight = 0;
    }

};
typedef AVLTSTNode* AVLTSTNodePointer;

struct TSTParentChildWay {

    AVLTSTNodePointer parent;
    AVLTSTNodePointer child;
    int tranisiton;

    TSTParentChildWay(AVLTSTNodePointer parent, AVLTSTNodePointer child, int tranisiton)
        : parent(parent), child(child), tranisiton(tranisiton){}

    TSTParentChildWay (AVLTSTNodePointer child) : child(child) {
        tranisiton = 2;
        parent = 0;
    }

};

class AVLTST {

public:
    AVLTST();
    AVLTSTNodePointer get(const char*);

    int getHeight();
    int getSize();
    AVLTSTNodePointer add(const char*);
    bool clear();
    AVLTSTNodePointer remove(const char*);
    LinkedList<AVLTSTNode> *traverse();

private:
    AVLTSTNodePointer root;
    AVLTSTNodePointer getNode(const char*);
    void traverseHelper(LinkedList<AVLTSTNode>*, AVLTSTNodePointer);
    void getLevelOrder(Stack<TSTParentChildWay*>*, AVLTSTNodePointer);
    void rotateRR(AVLTSTNodePointer, AVLTSTNodePointer, int);
    void rotateRL(AVLTSTNodePointer, AVLTSTNodePointer, int);
    void rotateLL(AVLTSTNodePointer, AVLTSTNodePointer, int);
    void rotateLR(AVLTSTNodePointer, AVLTSTNodePointer, int);
    void fixNode(AVLTSTNodePointer, AVLTSTNodePointer, int);
    void recalculateHeight(AVLTSTNodePointer);
    int getMaxNodeHeight(AVLTSTNodePointer);
    int getHeightHelper(AVLTSTNodePointer);
    void refixTree(AVLTSTNodePointer);

};


#endif // AVLTST_H
