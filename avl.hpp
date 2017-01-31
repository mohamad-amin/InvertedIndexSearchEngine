#include <avl.h>
#include <QDebug>

template <typename T>
AVL<T>::AVL() {
    this->root = NULL;
}

template <typename T>
void AVL<T>::recalculateHeight(AVLNode<T> *root) {
    if (root) {
//        qDebug() << "gonna calc " << root->data.c_str();
        if (root->leftChild) recalculateHeight(root->leftChild);
        if (root->rightChild)recalculateHeight(root->rightChild);
        root->leftHeight = getMaxNodeHeight(root->leftChild) + 1;
        root->rightHeight = getMaxNodeHeight(root->rightChild) + 1;
//        qDebug() << "calculated" << root->data.c_str() << "with LH" << root->leftHeight << "and RH" << root->rightHeight;
        if (root->leftChild) {
//            qDebug() << "it's left child:" << root->leftChild->data.c_str();
        }
        if (root->rightChild) {
//            qDebug() << "it's right child:" << root->rightChild->data.c_str();
        }
    }
//        Stack<ParentChildWay<T>*> *stack = new Stack<ParentChildWay<T>*>;
//        getLevelOrder(stack, root);

//        while (stack->getSize()) {
//            ParentChildWay<T> *bag = stack->pop();
//            if (bag->child) {
//                bag->child->leftHeight = getMaxNodeHeight(root->leftChild) + 1;
//                bag->child->rightHeight = getMaxNodeHeight(root->rightChild) + 1;
//            }
//        }
//    }
}

template <typename T>
int AVL<T>::getHeightHelper(AVLNode<T> *root) {
    if (!root) return 0;
    return std::max(getHeightHelper(root->leftChild), getHeightHelper(root->rightChild)) + 1;
}

template <typename T>
int AVL<T>::getHeight() {
    return getHeightHelper(this->root);
}

template <typename T>
int getSizeHelper(AVLNode<T> *root) {
    if (!root) return 0;
    return getSizeHelper(root->leftChild) + getSizeHelper(root->rightChild) + 1;
}

template <typename T>
int AVL<T>::getSize() {
    return getSizeHelper(this->root);
}

template <typename T>
AVLNode<T>* addHelper(AVLNode<T> *root, T data, Stack<AVLNode<T>*> *nodes, Stack<bool> *isLeftStep) {

    if (data > root->data) {
        nodes->push(root);
        isLeftStep->push(true);
        if (root->rightChild) {
            return addHelper(root->rightChild, data, nodes, isLeftStep);
        } else {
            return root->rightChild = new AVLNode<T>(data, NULL, NULL);
        }
    } else if (data < root->data) {
        nodes->push(root);
        isLeftStep->push(false);
        if (root->leftChild) {
            return addHelper(root->leftChild, data, nodes, isLeftStep);
        } else {
            return root->leftChild = new AVLNode<T>(data, NULL, NULL);
        }
    } else {
        // Already exists
        return root;
    }

}

template <typename T>
int balanceFactor(AVLNode<T> *node) {
    if (!node) {
        return 0;
    }
    return node->leftHeight - node->rightHeight;
}

template <typename T>
void AVL<T>::fixNode(AVLNode<T> *parent, AVLNode<T> *node, bool isLeftChild) {
    if (!node) {
        return;
    }
//    qDebug() << "gonna fix" << node->data.c_str() << "with parent" << parent;
    int bf = balanceFactor(node);
    if (bf <= -2) {
        AVLNode<T> *nextNode = node->rightChild;
        if (nextNode) {
            if (balanceFactor(nextNode) < 0) {
                // to right of it
                this->rotateRR(parent, node, isLeftChild);
            } else {
                this->rotateRL(parent, node, isLeftChild);
            }
        }
    } else if (bf >= 2) {
        // left problem
        AVLNode<T> *nextNode = node->leftChild;
        if (nextNode) {
            if (balanceFactor(nextNode) < 0) {
                // to right of it
                this->rotateLR(parent, node, isLeftChild);
            } else {
                this->rotateLL(parent, node, isLeftChild);
            }
        }
    }
}

template <typename T>
AVLNode<T>* AVL<T>::add(T data) {

    AVLNode<T> *result = get(data);
    if (result) {
        return result;
    }

    Stack<AVLNode<T>*> *nodes = new Stack<AVLNode<T>*>;
    Stack<bool> *isLeftStep = new Stack<bool>;

    if (this->root) {
        result = addHelper(this->root, data, nodes, isLeftStep);
        recalculateHeight(this->root);
        refixTree(this->root);
    } else {
        this->root = new AVLNode<T>(data, NULL, NULL);
        result = this->root;
    }

    return result;

}

template <typename T>
void AVL<T>::refixTree(AVLNode<T> *root) {

    Stack<ParentChildWay<T>*> *stack = new Stack<ParentChildWay<T>*>;
    getLevelOrder(stack, root);

    while (stack->getSize()) {
        ParentChildWay<T> *bag = stack->pop();
        fixNode(bag->parent, bag->child, bag->isLeft);
    }

}

template <typename T>
void AVL<T>::getLevelOrder(Stack<ParentChildWay<T>*> *result, AVLNode<T> *root) {
    LinkedList<ParentChildWay<T>*> *queue = new LinkedList<ParentChildWay<T>*>;
    ParentChildWay<T> *firstBag = new ParentChildWay<T>(root);
    queue->add(firstBag);
    while (queue->getSize() > 0) {
        ParentChildWay<T> *bag = queue->remove(0);
//        qDebug() << "adding to stack: " << bag->child->data.c_str();
        result->push(bag);
        if (bag->child->leftChild) {
            queue->add(new ParentChildWay<T>(bag->child, bag->child->leftChild, false)); // todo : check this
        }
        if (bag->child->rightChild) {
            queue->add(new ParentChildWay<T>(bag->child, bag->child->rightChild, true));
        }
    }
}

template <typename T>
AVLNode<T>* findMin(AVLNode<T> *root) {
    while (root->leftChild != NULL) root = root->leftChild;
    return root;
}

template <typename T>
AVLNode<T>* removeHelper(AVLNode<T> *root, T data) {

    if (!root) {
        return NULL;
    }

    if (data < root->data) {
        root->leftChild = removeHelper(root->leftChild, data);
    } else if (data > root->data) {
        root->rightChild = removeHelper(root->rightChild, data);
    } else {

        AVLNode<T> *tempNode;

        if (root->rightChild == NULL) {
            tempNode = root->leftChild;
            delete root;
            return tempNode;
        } else if (root->leftChild == NULL) {
            tempNode = root->rightChild;
            delete root;
            return tempNode;
        }

        tempNode = findMin(root->rightChild);
        root->data = tempNode->data;
        root->rightChild = removeHelper(root->rightChild, tempNode->data);

    }

    return root;

}

template <typename T>
AVLNode<T>* AVL<T>::remove(T data) {
    AVLNode<T> *result = removeHelper(this->root, data);
    if (result) {
        recalculateHeight(this->root);
        refixTree(this->root);
    }
    return result;
}

template <typename T>
bool clearHelper(AVLNode<T> *root) {
    if (!root) {
        return true;
    }
    if (root->leftChild) {
        clearHelper(root->leftChild);
    }
    if (root->rightChild) {
        clearHelper(root->rightChild);
    }
    delete root;
    return true;
}

template <typename T>
bool AVL<T>::clear() {
    return clearHelper(this->root);
}

template <typename T>
AVLNode<T>* AVL<T>::getNode(AVLNode<T> *root, T data) {
    if (!root) {
        return root;
    }
    if (data > root->data) {
        return getNode(root->rightChild, data);
    } else if (data < root->data) {
        return getNode(root->leftChild, data);
    } else {
        return root;
    }
}

template <typename T>
AVLNode<T> * AVL<T>::get(T data) {
    return getNode(this->root, data);
}

template <typename T>
void AVL<T>::getInorder(LinkedList<AVLNode<T> > *list, AVLNode<T>* root) {
    if (root) {
        getInorder(list, root->leftChild);
        list->add(*root);
        getInorder(list, root->rightChild);
    }
}

template <typename R>
LinkedList<AVLNode<R> >* AVL<R>::getNodesInInorder() {
    LinkedList<AVLNode<R> > *list = new LinkedList<AVLNode<R> >;
    getInorder(list, this->root);
    return list;
}

template <typename T>
int AVL<T>::getMaxNodeHeight(AVLNode<T> *node) {
    if (!node) {
        return -1;
    }
    int max = node->leftHeight;
    if (node->rightHeight > max) {
        max = node->rightHeight;
    }
    return max;
}

template <typename T>
void AVL<T>::rotateLL(AVLNode<T> *parent, AVLNode<T> *node, bool isLeftChild) {
    AVLNode<T> *nextRoot = node->leftChild;
    AVLNode<T> *nextLeft = nextRoot->rightChild;
    nextRoot->rightChild = node;
    node->leftChild = nextLeft;
    if (parent) {
        if (isLeftChild) {
            parent->rightChild = nextRoot;
        } else {
            parent->leftChild = nextRoot;
        }
    } else {
        this->root = nextRoot;
    }
    recalculateHeight(this->root);
}

template <typename T>
void AVL<T>::rotateRR(AVLNode<T> *parent, AVLNode<T> *node, bool isLeftChild) {
    AVLNode<T> *nextRoot = node->rightChild;
    AVLNode<T> *nextRight = nextRoot->leftChild;
    nextRoot->leftChild = node;
    node->rightChild = nextRight;
    if (parent) {
        if (isLeftChild) {
            parent->rightChild = nextRoot;
        } else {
            parent->leftChild = nextRoot;
        }
    } else {
        this->root = nextRoot;
    }
    recalculateHeight(this->root);
}

template <typename T>
void AVL<T>::rotateLR(AVLNode<T> *parent, AVLNode<T> *node, bool isLeftChild) {
    AVLNode<T> *left = node->leftChild;
    AVLNode<T> *nextLeft = left->rightChild;
    AVLNode<T> *nextLeftLeftRight = nextLeft->leftChild;
    node->leftChild = nextLeft;
    nextLeft->leftChild = left;
    left->rightChild = nextLeftLeftRight;
    rotateLL(parent, node, isLeftChild);
}

template <typename T>
void AVL<T>::rotateRL(AVLNode<T> *parent, AVLNode<T> *node, bool isLeftChild) {
    AVLNode<T> *right = node->rightChild;
    AVLNode<T> *nextRight = right->leftChild;
    AVLNode<T> *nextRightRightLeft = nextRight->rightChild;
    node->rightChild = nextRight;
    nextRight->rightChild = right;
    right->leftChild = nextRightRightLeft;
    rotateRR(parent, node, isLeftChild);
}
