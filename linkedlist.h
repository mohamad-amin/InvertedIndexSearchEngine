#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <class type>
struct ListNode {

public:
    ListNode();
    ListNode(type &data);

    type data;
    ListNode<type> *next;

};

template <class T>
class LinkedList {

public:
    LinkedList();
    ~LinkedList();
    int getSize();
    bool add(T);
    bool add(int, T);
    T remove(int);
    T get(int);
    void getAsArray(T*);
    T pop();
    bool clear();

private:
    int size;
//    int lastGotIndex;
    ListNode<T> *first;
    ListNode<T> *last;
//    ListNode<T> *lastGot;

    ListNode<T>* getNode(int index);

};

template <class type>
ListNode<type>::ListNode() {
    this->next = 0;
}

template <class type>
ListNode<type>::ListNode(type &data) {
    this->data = data;
}

#include "linkedlist.hpp"

#endif // LINKEDLIST_H
