#include "hashmap.h"

HashMap::HashMap() {
    this->size = 0;
    this->table = new HashEntry*[TABLE_SIZE];
    for (int i=0; i<TABLE_SIZE; i++) {
        this->table[i] = NULL;
    }
}

int HashMap::getHashCode(const char *word) {
    int result = 0;
    for (int i=0; i<strlen(word); i++) {
        result += (i%2) ? toupper(word[i]) : word[i];
    }
    return result;
}

HashEntry* HashMap::add(const char *word) {

    int hashCode = getHashCode(word);
    while (table[hashCode] != NULL && *table[hashCode]->getKey() != std::string(word)) {
        hashCode = (hashCode + 1) % TABLE_SIZE;
    }

    HashEntry *temp = table[hashCode];
    if (temp == NULL) {
        temp = new HashEntry(new std::string(word));
        table[hashCode] = temp;
        this->size++;
    }
    return temp;

}

HashEntry* HashMap::get(const char *word) {
    int hashCode = getHashCode(word);
    while (table[hashCode] != NULL && *(table[hashCode]->getKey()) != std::string(word)) {
        hashCode = (hashCode + 1) % TABLE_SIZE;
    }
    return table[hashCode];
}

bool HashMap::remove(const char *word) {
    int hashCode = getHashCode(word);
    while (table[hashCode] != NULL && *(table[hashCode]->getKey()) != std::string(word)) {
        hashCode = (hashCode + 1) % TABLE_SIZE;
    }
    if (table[hashCode]) {
        delete table[hashCode];
        table[hashCode] = NULL;
        this->size--;
        return true;
    }
    return false;
}

LinkedList<HashEntry*>* HashMap::traverse() {
    LinkedList<HashEntry*> *list = new LinkedList<HashEntry*>;
    for (int i=0; i<TABLE_SIZE; i++) {
        if (table[i]) {
            list->add(table[i]);
        }
    }
    return list;
}

int HashMap::getSize() {
    return this->size;
}

HashMap::~HashMap() {
    for (int i=0; i<TABLE_SIZE; i++) {
        if (table[i]) {
            delete table[i];
        }
    }
    delete table;
    this->size = -1;
}
