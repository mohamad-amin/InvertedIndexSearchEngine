#ifndef STACK_H
#define STACK_H

template <class type>
struct StackNode {

public:
    StackNode();
    StackNode(type &data);

    type data;
    StackNode<type> *next;

};

template <class T>
class Stack {

public:
    Stack();
    ~Stack();
    int getSize();
    bool push(T);
    T pop();
    T getBefore();
    void getAsArray(T*);
    bool clear();

private:
    int size;
    StackNode<T> *last;

};

template <class type>
StackNode<type>::StackNode() {
    this->next = 0;
}

template <class type>
StackNode<type>::StackNode(type &data) {
    this->data = data;
}

#include "stack.hpp"

#endif // STACK_H
