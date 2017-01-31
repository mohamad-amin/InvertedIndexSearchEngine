#include "avltst.h"
#include <cstring>
#include <iostream>

AVLTST::AVLTST() {
    this->root = NULL;
}

int balanceFactor(AVLTSTNodePointer node) {
    if (!node) {
        return 0;
    }
    return node->leftHeight - node->rightHeight;
}

void AVLTST::recalculateHeight(AVLTSTNodePointer root) {
    if (root) {
        recalculateHeight(root->rightChild);
        recalculateHeight(root->middleChild);
        recalculateHeight(root->leftChild);
        root->leftHeight = getMaxNodeHeight(root->leftChild) + 1;
        root->rightHeight = getMaxNodeHeight(root->rightChild) + 1;
    }
}

AVLTSTNodePointer AVLTST::getNode(const char *c) {
    AVLTSTNodePointer temp = this->root;
    while (temp && c[0] != '\0') {
        if (temp->data < c[0]) {
            temp = temp->rightChild;
        } else if (temp->data > c[0]) {
            temp = temp->leftChild;
        } else {
            if (c[1] == '\0' && temp->isEndOfWord) {
                return temp;
            }
            c++;
            temp = temp->middleChild;
        }
    }
    return NULL;
}

AVLTSTNodePointer addHelper(AVLTSTNodePointer root, const char *word, Stack<AVLTSTNodePointer> *nodes, Stack<int> *transitions) {

    AVLTSTNodePointer temp;

    if (!root) {
        root = new AVLTSTNode(word[0]);
        temp = root;
        for (int i = 1; i < strlen(word); i++) {
            temp->middleChild = new AVLTSTNode(word[i]);
            temp = temp->middleChild;
        }
    } else {

        char data;
        temp = root;

        for (int i=0; i < strlen(word);) {
            data = word[i];
            if (data < temp->data) {
                nodes->push(temp);
                transitions->push(0); // left
                if (!temp->leftChild)
                    temp->leftChild = new AVLTSTNode(data);
                temp = temp->leftChild;
            } else if (data > temp->data) {
                transitions->push(2); // right
                nodes->push(temp);
                if (!temp->rightChild)
                    temp->rightChild = new AVLTSTNode(data);
                temp = temp->rightChild;
            } else {
                if (word[i+1]) {
                    nodes->push(temp);
                    transitions->push(1); // mid
                    if (!temp->middleChild)
                        temp->middleChild = new AVLTSTNode(word[i + 1]);
                    temp = temp->middleChild;
                }
                i++;
            }
        }

    }

    temp->isEndOfWord = true;
    temp->word = new std::string(word);

    return temp;

}

void AVLTST::fixNode(AVLTSTNodePointer parent, AVLTSTNodePointer node, int transition) {
    int bf = balanceFactor(node);
    if (bf <= -2) {
        AVLTSTNodePointer nextNode = node->rightChild;
        if (nextNode) {
            if (balanceFactor(nextNode) < 0) {
                // to right of it
                this->rotateRR(parent, node, transition);
            } else {
                this->rotateRL(parent, node, transition);
            }
        }
    } else if (bf >= 2) {
        // left problem
        AVLTSTNodePointer nextNode = node->leftChild;
        if (nextNode) {
            if (balanceFactor(nextNode) < 0) {
                // to right of it
                this->rotateLR(parent, node, transition);
            } else {
                this->rotateLL(parent, node, transition);
            }
        }
    }
}

void AVLTST::refixTree(AVLTSTNodePointer root) {

    Stack<TSTParentChildWay*> *stack = new Stack<TSTParentChildWay*>;
    getLevelOrder(stack, root);

    while (stack->getSize()) {
        TSTParentChildWay *bag = stack->pop();
        fixNode(bag->parent, bag->child, bag->tranisiton);
    }

}

AVLTSTNodePointer AVLTST::add(const char *word) {

    AVLTSTNodePointer temp;
//    std::cout << "adding " << word << " ==> ";

    if (!this->root) {
        this->root = new AVLTSTNode(word[0]);
        temp = this->root;
        for (int i = 1; i < strlen(word); i++) {
            temp->middleChild = new AVLTSTNode(word[i]);
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
                    temp->leftChild = new AVLTSTNode(data);
                temp = temp->leftChild;
            } else if (data > temp->data) {
                if (!temp->rightChild)
                    temp->rightChild = new AVLTSTNode(data);
                temp = temp->rightChild;
            } else {
                if (word[i+1]) {
                    if (!temp->middleChild)
                        temp->middleChild = new AVLTSTNode(word[i + 1]);
                    temp = temp->middleChild;
                }
                i++;
            }
        }

    }

    temp->isEndOfWord = true;
    temp->word = new std::string(word);
//    std::cout << " ==> " << *temp->word << " || last node: " << temp->data << std::endl;

    recalculateHeight(this->root);
    refixTree(this->root);

    return temp;

//    return addHelper(&this->root, word, 0);

}

void AVLTST::getLevelOrder(Stack<TSTParentChildWay*> *result, AVLTSTNodePointer root) {
    if (!root) {
        return;
    }
    LinkedList<TSTParentChildWay*> *queue = new LinkedList<TSTParentChildWay*>;
    TSTParentChildWay *firstBag = new TSTParentChildWay(root);
    queue->add(firstBag);
    while (queue->getSize() > 0) {
        TSTParentChildWay *bag = queue->remove(0);
        result->push(bag);
        if (bag->child->leftChild) {
            queue->add(new TSTParentChildWay(bag->child, bag->child->leftChild, 0)); // todo : check this
        }
        if (bag->child->middleChild) {
            queue->add(new TSTParentChildWay(bag->child, bag->child->middleChild, 1)); // todo : check this
        }
        if (bag->child->rightChild) {
            queue->add(new TSTParentChildWay(bag->child, bag->child->rightChild, 2)); // todo : check this
        }
    }
}

AVLTSTNodePointer AVLTST::get(const char *c) {
    return getNode(c);
}

int getSizeHelper(AVLTSTNodePointer root) {
    if (!root) return 0;
    int size = 1;
    size += getSizeHelper(root->leftChild);
    size += getSizeHelper(root->rightChild);
    size += getSizeHelper(root->middleChild);
    return size;
}

int AVLTST::getSize() {
    return getSizeHelper(this->root);
}

int AVLTST::getHeightHelper(AVLTSTNodePointer root) {
    if (!root) return 0;
    return std::max(getHeightHelper(root->middleChild)+1,
               std::max(getHeightHelper(root->leftChild), getHeightHelper(root->rightChild)));
}

int AVLTST::getHeight() {
    return getHeightHelper(this->root);
}

int AVLTST::getMaxNodeHeight(AVLTSTNodePointer node) {
    if (!node) {
        return -1;
    }
    int max = node->leftHeight;
    if (node->rightHeight > max) {
        max = node->rightHeight;
    }
    return max;
}

AVLTSTNodePointer removeHelper(AVLTSTNodePointer root, const char *c) {
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

AVLTSTNodePointer AVLTST::remove(const char *c) {
    AVLTSTNodePointer result = removeHelper(this->root, c);
    if (result) {
        recalculateHeight(this->root);
        refixTree(this->root);
    }
    return result;
}

bool clearHelper(AVLTSTNodePointer root) {
    if (root) {
        clearHelper(root->leftChild);
        clearHelper(root->rightChild);
        clearHelper(root->middleChild);
        delete root;
        return true;
    }
    return false;
}

bool AVLTST::clear() {
    return clearHelper(this->root);
}

void AVLTST::traverseHelper(LinkedList<AVLTSTNode> *list, AVLTSTNodePointer root) {
    if (root) {
        traverseHelper(list, root->leftChild);
        if (root->isEndOfWord) {
            list->add(*root);
        }
        traverseHelper(list, root->middleChild);
        traverseHelper(list, root->rightChild);
    }
}

LinkedList<AVLTSTNode>* AVLTST::traverse() {
    LinkedList<AVLTSTNode> *list = new LinkedList<AVLTSTNode>;
    traverseHelper(list, this->root);
    return list;
}

void AVLTST::rotateLL(AVLTSTNodePointer parent, AVLTSTNodePointer node, int transition) {
    AVLTSTNodePointer nextRoot = node->leftChild;
    AVLTSTNodePointer nextLeft = nextRoot->rightChild;
    nextRoot->rightChild = node;
    node->leftChild = nextLeft;
    if (parent) {
        if (!transition) {
            parent->leftChild = nextRoot;
        } else if (transition == 1) {
            parent->middleChild = nextRoot;
        } else {
            parent->rightChild = nextRoot;
        }
    } else {
        this->root = nextRoot;
    }
    recalculateHeight(this->root);
}

void AVLTST::rotateRR(AVLTSTNodePointer parent, AVLTSTNodePointer node, int transition) {
    AVLTSTNodePointer nextRoot = node->rightChild;
    AVLTSTNodePointer nextRight = nextRoot->leftChild;
    nextRoot->leftChild = node;
    node->rightChild = nextRight;
    if (parent) {
        if (!transition) {
            parent->leftChild = nextRoot;
        } else if (transition == 1) {
            parent->middleChild = nextRoot;
        } else {
            parent->rightChild = nextRoot;
        }
    } else {
        this->root = nextRoot;
    }
    recalculateHeight(this->root);
}

void AVLTST::rotateLR(AVLTSTNodePointer parent, AVLTSTNodePointer node, int transition) {
    AVLTSTNodePointer left = node->leftChild;
    AVLTSTNodePointer nextLeft = left->rightChild;
    AVLTSTNodePointer nextLeftLeftRight = nextLeft->leftChild;
    node->leftChild = nextLeft;
    nextLeft->leftChild = left;
    left->rightChild = nextLeftLeftRight;
    recalculateHeight(this->root);
    rotateLL(parent, node, transition);
}

void AVLTST::rotateRL(AVLTSTNodePointer parent, AVLTSTNodePointer node, int transition) {
    AVLTSTNodePointer right = node->rightChild;
    AVLTSTNodePointer nextRight = right->leftChild;
    AVLTSTNodePointer nextRightRightLeft;
    nextRightRightLeft = nextRight->rightChild;
    node->rightChild = nextRight;
    nextRight->rightChild = right;
    right->leftChild = nextRightRightLeft;
    recalculateHeight(this->root);
    rotateRR(parent, node, transition);
}
