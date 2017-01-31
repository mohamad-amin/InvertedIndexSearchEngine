#ifndef TRIEWRAPPER_H
#define TRIEWRAPPER_H

#include <trie.h>
#include <fileprocessor.h>
#include <stopwords.h>
#include <fileholder.h>

class TrieWrapper {

public:
    TrieWrapper(StopWords *stopWords, FileHolder *fileHolder);
    void addFile(QFile*, int);
    void removeFile(QFile*);
    void updateFile(QFile*);
    void search(std::string, std::string*);
    LinkedList<std::string>* listAllWords();
    void searchSentence(LinkedList<std::string>*, std::string*);
    int getCount();

private:
    Trie *trie;
    StopWords *stopWords;
    FileHolder *fileHolder;
    bool contains(LinkedList<CustomFile*> *customFiles, CustomFile *customFile);

};

#endif // TRIEWRAPPER_H
