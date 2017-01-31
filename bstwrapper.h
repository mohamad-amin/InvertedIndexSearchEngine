#ifndef BSTWRAPPER_H
#define BSTWRAPPER_H

#include <avl.h>
#include <stopwords.h>
#include <fileprocessor.h>
#include <fileholder.h>

class BSTWrapper {

public:
    BSTWrapper(StopWords *stopWords, FileHolder *fileHolder);
    void addFile(QFile*, int);
    void removeFile(QFile*);
    void updateFile(QFile*);
    void search(std::string, std::string*);
    LinkedList<std::string>* listAllWords();
    void searchSentence(LinkedList<std::string>*, std::string*);

private:
    AVL<std::string> *bst;
    StopWords *stopWords;
    FileHolder *fileHolder;
    bool contains(LinkedList<CustomFile*> *customFiles, CustomFile *customFile);

};

#endif // BSTWRAPPER_H
