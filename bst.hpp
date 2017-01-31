template <typename T>
BST<T>::BST() {
    this->root = NULL;
}

template <typename T>
int getHeightHelper(TreeNode<T> *root) {
    if (!root) return 0;
    return max(getHeightHelper(root->leftChild), getHeightHelper(root->rightChild)) + 1;
}

template <typename T>
int BST<T>::getHeight() {
    return getHeightHelper(this->root);
}

template <typename T>
int getSizeHelper(TreeNode<T> *root) {
    if (!root) return 0;
    return getSizeHelper(root->leftChild) + getSizeHelper(root->rightChild) + 1;
}

template <typename T>
int BST<T>::getSize() {
    return getSizeHelper(this->root);
}

template <typename T>
TreeNode<T>* addHelper(TreeNode<T> *root, T data) {

    if (data > root->data) {
        if (root->rightChild) {
            return addHelper(root->rightChild, data);
        } else {
            return root->rightChild = new TreeNode<T>(data, NULL, NULL);
        }
    } else if (data < root->data) {
        if (root->leftChild) {
            return addHelper(root->leftChild, data);
        } else {
            return root->leftChild = new TreeNode<T>(data, NULL, NULL);
        }
    } else {
        // Already exists
        return root;
    }

}

template <typename T>
TreeNode<T>* BST<T>::add(T data) {
    if (this->root) {
        return addHelper(this->root, data);
    } else {
        this->root = new TreeNode<T>(data, NULL, NULL);
        return this->root;
    }
}

template <typename T>
TreeNode<T>* findMin(TreeNode<T> *root) {
    while (root->leftChild != NULL) root = root->leftChild;
    return root;
}

template <typename T>
TreeNode<T>* removeHelper(TreeNode<T> *root, T data) {

    if (!root) {
        return NULL;
    }

    if (data < root->data) {
        root->leftChild = removeHelper(root->leftChild, data);
    } else if (data > root->data) {
        root->rightChild = removeHelper(root->rightChild, data);
    } else {

        TreeNode<T> *tempNode;

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
TreeNode<T>* BST<T>::remove(T data) {
    return removeHelper(this->root, data);
}

template <typename T>
bool clearHelper(TreeNode<T> *root) {
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
bool BST<T>::clear() {
    return clearHelper(this->root);
}

template <typename T>
TreeNode<T>* BST<T>::getNode(TreeNode<T> *root, T data) {
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
TreeNode<T> * BST<T>::get(T data) {
    return getNode(this->root, data);
}

template <typename T>
void BST<T>::getInorder(LinkedList<TreeNode<T> > *list, TreeNode<T>* root) {
    if (root) {
        getInorder(list, root->leftChild);
        list->add(*root);
        getInorder(list, root->rightChild);
    }
}

template <typename R>
LinkedList<TreeNode<R> >* BST<R>::getNodesInInorder() {
    LinkedList<TreeNode<R> > *list = new LinkedList<TreeNode<R> >;
    getInorder(list, this->root);
    return list;
}
