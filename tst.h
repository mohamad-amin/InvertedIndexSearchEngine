#ifndef TST_H
#define TST_H

#include "customfile.h"
#include "linkedlist.h"

struct TSTNode {

    LinkedList<CustomFile*> *list;
    std::string *word;

    char data;
    TSTNode* leftChild;
    TSTNode* rightChild;
    TSTNode* middleChild;
    bool isEndOfWord;

    TSTNode(char data) : data(data) {
        this->leftChild = NULL;
        this->middleChild = NULL;
        this->rightChild = NULL;
        this->list = new LinkedList<CustomFile*>;
    }

    TSTNode(char data, TSTNode* leftChild, TSTNode* middleChild, TSTNode* rightChild) {
        this->data = data;
        this->leftChild = leftChild;
        this->middleChild = middleChild;
        this->rightChild = rightChild;
        this->list = new LinkedList<CustomFile*>;
        this->isEndOfWord = false;
    }

    TSTNode() {
        this->list = new LinkedList<CustomFile*>;
        leftChild = NULL;
        middleChild = NULL;
        rightChild = NULL;
        this->isEndOfWord = false;
    }

};
typedef TSTNode* TSTNodePointer;

class TST {

public:
    TST();
    TSTNodePointer get(const char*);
    int getHeight();
    int getSize();
    TSTNodePointer add(const char*);
    bool clear();
    TSTNodePointer remove(const char*);
    LinkedList<TSTNode> *traverse();

private:
    TSTNodePointer root;
    TSTNodePointer getNode(const char*);
    void traverseHelper(LinkedList<TSTNode>*, TSTNodePointer);

};

#endif // TST_H
