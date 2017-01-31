#include <QDebug>

template <class T>
LinkedList<T>::LinkedList() {
    this->first = new ListNode<T>();
    this->first->next = 0;
    this->last = first;
    this->size = 0;
//    this->lastGot = 0;
//    this->lastGotIndex = -1;
}

template <class T>
LinkedList<T>::~LinkedList() {
    this->clear();
}

template <class T>
int LinkedList<T>::getSize() {
    return this->size;
}

template <class T>
bool LinkedList<T>::add(int index, T data) {

    ListNode<T> *newNode = new ListNode<T>;
    newNode->data = data;

    if (index == getSize()) {
        newNode->next = 0;
        this->last->next = newNode;
        this->last = newNode;
    } else {
        ListNode<T> *previousNode = getNode(index-1);
        newNode->next = previousNode->next;
        previousNode->next = newNode;
    }

    this->size++;
    return true;

}

template <class T>
bool LinkedList<T>::add(T data) {
    return add(getSize(), data);
}

template <class T>
ListNode<T>* LinkedList<T>::getNode(int index) {

    int realIndex = index;

    if (index == -1) {
        return first;
    } else if (index == size-1) {
        return this->last;
    }

    ListNode<T> *currentNode = first;
//    if (lastGotIndex > -1 && lastGot != 0 && index >= lastGotIndex) {
//        currentNode = lastGot;
//        index -= lastGotIndex;
//    } else {
//        currentNode = first;
//        index++;
//    }

    index++;
    while (index--) {
        currentNode = currentNode->next;
    }

//    lastGotIndex = realIndex;
//    lastGot = currentNode;
    return currentNode;

}

template <class T>
void LinkedList<T>::getAsArray(T* array) {
    ListNode<T> *temp = this->first;
    int i=0;
    while (temp = temp->next) {
        array[i++] = temp->data;
    }
}

template <class T>
T LinkedList<T>::get(int index) {
    return getNode(index)->data;
}

template <class T>
T LinkedList<T>::remove(int index) {

    if (index > this->size - 1) {
        return 0;
    }

    ListNode<T> *deletedNode;
    ListNode<T> *currentNode = getNode(index-1);

    if (index == this->size-1) {
        deletedNode = currentNode->next;
        currentNode->next = 0;
        this->last = currentNode;
    } else {
        deletedNode = currentNode->next;
        currentNode->next = deletedNode->next;
    }

    size--;
//    if (index <= lastGotIndex) {
//        lastGotIndex--;
//    }
    T data = deletedNode->data;
    delete deletedNode;
    return data;

}

template <class T>
T LinkedList<T>::pop() {
    remove(this->size-1);
}

template <class T>
bool LinkedList<T>::clear() {
    while (this->size) {
        remove(this->size-1);
    }
    return true;
}
