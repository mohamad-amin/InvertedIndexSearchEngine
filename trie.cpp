#include "trie.h"

Trie::Trie() {
    this->root = new TrieNode;
}

TrieNodePointer Trie::add(const char *c) {

    std::string *word = new std::string(c);
    TrieNodePointer temp = this->root;
    while (*c) {      // Until there is something to process
        if (!temp->children[*c - 'a']) {
            // There is no node in 'trie_tree' corresponding to this alphabet
            // Allocate using calloc(), so that components are initialised
            temp->children[*c - 'a'] = new TrieNode(*c);
            temp->children[*c - 'a']->parent = temp; // Assigning parent
        }

        temp = temp->children[*c++ - 'a'];
    }
    temp->occurences++;
    temp->word = word;
    temp->isEndOfWord = true;
    return temp;
}

TrieNodePointer getHelper(TrieNodePointer root, const char* c) {
    TrieNodePointer temp = root;
    while (*c) {
        if (temp->children[*c - 'a'] != NULL) {
            temp = temp->children[*c++ - 'a'];
        } else {
            break;
        }
    }
    if (!*c && temp->occurences != 0) {
        // Word found
        return temp;
    } else {
        // Word not found
        return NULL;
    }
}

TrieNodePointer Trie::get(const char *c) {
    return getHelper(this->root, c);
}

bool Trie::remove(const char *word) {

    TrieNodePointer temp = getHelper(this->root, word);

    if (temp == NULL) {
        // Word not found
        return false;
    }

    temp->occurences--;

    // 'noChild' indicates if the node is a leaf node
    bool noChild = true;

    int childCount = 0;
    // 'childCount' has the number of children the current node
    // has which actually tells us if the node is associated with
    // another word .This will happen if 'childCount' >= 2.
    int i;
    // Checking children of current node
    for (i=0; i<26; i++) {
        if (temp->children[i] != NULL) {
            noChild = false;
            childCount++;
        }
    }

    if (!noChild) {
        // The node has children, which means that the word whose
        // occurrence was just removed is a Suffix-Word
        // So, logically no more nodes have to be deleted
        return true;
    }

    TrieNodePointer traverse;
    while (temp->occurences == 0 && temp->parent != NULL && childCount < 2) {

        traverse = temp->parent;

        for (i = 0; i < 26; i++) {
            if (temp == traverse->children[i]) {
                traverse->children[i] = NULL;
                break;
            }
        }

        delete temp;
        temp = traverse;

        for (i = 0; i < 26; ++i) {
            if (temp->children[i] != NULL) {
                ++childCount;
            }
        }
    }

    return true;

}


void Trie::traverseHelper(LinkedList<TrieNode> *list, TrieNodePointer root) {
    if (root) {
        if (root->isEndOfWord) {
            list->add(*root);
        }
        for (int i=0; i<26; i++) {
            traverseHelper(list, root->children[i]);
        }
    }
}

LinkedList<TrieNode>* Trie::traverse() {
    LinkedList<TrieNode> *list = new LinkedList<TrieNode>;
    traverseHelper(list, this->root);
    return list;
}
