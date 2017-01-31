template <class T>
Stack<T>::Stack() {
    this->last = 0;
    this->size = 0;
}

template <class T>
Stack<T>::~Stack() {
    this->clear();
}

template <class T>
int Stack<T>::getSize() {
    return this->size;
}

template <class T>
bool Stack<T>::push(T data) {
    StackNode<T> *newNode = new StackNode<T>;
    newNode->data = data;
    if (this->last) {
        newNode->next = last;
    }
    last = newNode;
    size++;
    return true;
}

template <class T>
void Stack<T>::getAsArray(T* array) {
    StackNode<T> *temp = this->last;
    int i=0;
    while (temp = temp->next) {
        array[i++] = temp->data;
    }
}

template <class T>
T Stack<T>::getBefore() {
    if (this->last) {
        return this->last->data;
    } else {
        return 0;
    }
}

template <class T>
T Stack<T>::pop() {
    StackNode<T> *result = this->last;
    if (last) {
        this->last = this->last->next;
        T data = result->data;
        this->size--;
        return data;
    } else {
        return 0;
    }
}

template <class T>
bool Stack<T>::clear() {
    while (size) {
        pop();
    }
    return true;
}
