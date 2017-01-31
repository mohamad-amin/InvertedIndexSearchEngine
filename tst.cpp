#include "tst.h"
#include <cstring>
#include <iostream>

TST::TST() {
    this->root = NULL;
}

TSTNodePointer TST::getNode(const char *c) {
//    std::cout << c << " ==> " ;
    TSTNodePointer temp = this->root;
    while (temp && c[0] != '\0') {
//        std::cout << " || " << temp->data << "-" << c[0];
        if (temp->data < c[0]) {
//            std::cout << " (R)";
            temp = temp->rightChild;
        } else if (temp->data > c[0]) {
//            std::cout << " (L)";
            temp = temp->leftChild;
        } else {
            if (c[1] == '\0' && temp->isEndOfWord) {
                std::cout << " ==> " << *temp->word << std::endl;
                return temp;
            }
//            std::cout << " (M)";
            c++;
            temp = temp->middleChild;
        }
    }
//    std::cout << " ==> :( " << std::endl;
    return NULL;
}

TSTNodePointer TST::add(const char *word) {

    TSTNodePointer temp;
//    std::cout << "adding " << word << " ==> ";

    if (!this->root) {
        this->root = new TSTNode(word[0]);
        temp = this->root;
        for (int i = 1; i < strlen(word); i++) {
            temp->middleChild = new TSTNode(word[i]);
            temp = temp->middleChild;
        }
    } else {

        char data;
        temp = this->root;

        for (int i=0; i < strlen(word);) {
            data = word[i];
//            std::cout << data << "-" <<temp->data << " ";
            if (data < temp->data) {
                if (!temp->leftChild)
                    temp->leftChild = new TSTNode(data);
                temp = temp->leftChild;
            } else if (data > temp->data) {
                if (!temp->rightChild)
                    temp->rightChild = new TSTNode(data);
                temp = temp->rightChild;
            } else {
                if (word[i+1]) {
                    if (!temp->middleChild)
                        temp->middleChild = new TSTNode(word[i + 1]);
                    temp = temp->middleChild;
                }
                i++;
            }
        }

    }

    temp->isEndOfWord = true;
    temp->word = new std::string(word);
//    std::cout << " ==> " << *temp->word << " || last node: " << temp->data << std::endl;

    return temp;

//    return addHelper(&this->root, word, 0);

}

TSTNodePointer TST::get(const char *c) {
    return getNode(c);
}

int getSizeHelper(TSTNodePointer root) {
    if (!root) return 0;
    int size = 1;
    size += getSizeHelper(root->leftChild);
    size += getSizeHelper(root->rightChild);
    size += getSizeHelper(root->middleChild);
    return size;
}

int TST::getSize() {
    return getSizeHelper(this->root);
}

int getHeightHelper(TSTNodePointer root) {
    if (!root) return 0;
    return std::max(getHeightHelper(root->middleChild)+1,
               std::max(getHeightHelper(root->leftChild), getHeightHelper(root->rightChild)));
}

int TST::getHeight() {
    return getHeightHelper(this->root);
}

TSTNodePointer removeHelper(TSTNodePointer root, const char *c) {
    if (!root) return root;
    if (root->data > *c) {
        return removeHelper(root->leftChild, c);
    } else if (root->data < *c) {
        return removeHelper(root->rightChild, c);
    } else {
        if (root->isEndOfWord && !c[1]) {
            root->isEndOfWord = false;
            return root;
        } else if (c[1]) {
            return removeHelper(root->middleChild, ++c);
        }
        return NULL;
    }
}

TSTNodePointer TST::remove(const char *c) {
    return removeHelper(this->root, c);
}

bool clearHelper(TSTNodePointer root) {
    if (root) {
        clearHelper(root->leftChild);
        clearHelper(root->rightChild);
        clearHelper(root->middleChild);
        delete root;
        return true;
    }
    return false;
}

bool TST::clear() {
    return clearHelper(this->root);
}

void TST::traverseHelper(LinkedList<TSTNode> *list, TSTNodePointer root) {
    if (root) {
        traverseHelper(list, root->leftChild);
        if (root->isEndOfWord) {
            list->add(*root);
        }
        traverseHelper(list, root->middleChild);
        traverseHelper(list, root->rightChild);
    }
}

LinkedList<TSTNode>* TST::traverse() {
    LinkedList<TSTNode> *list = new LinkedList<TSTNode>;
    traverseHelper(list, this->root);
    return list;
}
