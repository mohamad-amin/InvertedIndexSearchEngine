#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <cstring>
#include <customfile.h>
#include <linkedlist.h>

struct HashEntry {

    std::string *key;
    LinkedList<CustomFile*> *value;

    HashEntry(std::string *key) : key(key) {
        this->value = new LinkedList<CustomFile*>;
    }

    void add(CustomFile *customFile) {
        value->add(customFile);
    }

    LinkedList<CustomFile*>* getValue() {
        return this->value;
    }

    std::string* getKey() {
        return this->key;
    }

};

class HashMap {

public:

    HashMap();
    ~HashMap();
    int getSize();
    bool remove(const char*);
    HashEntry* add(const char*);
    HashEntry* get(const char*);
    LinkedList<HashEntry*>* traverse();

private:

    int size;
    HashEntry **table;
    const int TABLE_SIZE = 1024;

    int getHashCode(const char*);

};

#endif // HASHMAP_H
