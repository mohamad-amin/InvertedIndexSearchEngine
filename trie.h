#ifndef TRIE_H
#define TRIE_H

#include <linkedlist.h>
#include <customfile.h>

struct TrieNode {

    LinkedList<CustomFile*> *list;
    std::string *word;

    char data;
    int occurences;
    TrieNode *parent;
    TrieNode *children[26];
    bool isEndOfWord = false;

    TrieNode(char data) : data(data) {
        list = new LinkedList<CustomFile*>;
        for (int i=0; i<26; i++) {
            children[i] = NULL;
        }
    }

    TrieNode() {
        list = new LinkedList<CustomFile*>;
        for (int i=0; i<26; i++) {
            children[i] = NULL;
        }
    }

};
typedef TrieNode* TrieNodePointer;

class Trie {

public:
    Trie();
    TrieNodePointer add(const char*);
    TrieNodePointer get(const char*);
    bool remove(const char*);
    LinkedList<TrieNode> *traverse();

private:
    TrieNodePointer root;
    TrieNodePointer getNode(char*);
    void traverseHelper(LinkedList<TrieNode>*, TrieNodePointer);

};

#endif // TRIE_H
