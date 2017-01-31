#ifndef TSTWRAPPER_H
#define TSTWRAPPER_H

#include <avltst.h>
#include <fileprocessor.h>
#include <stopwords.h>
#include <fileholder.h>

class TSTWrapper {

public:
    TSTWrapper(StopWords *stopWords, FileHolder *fileHolder);
    void addFile(QFile*, int);
    void removeFile(QFile*);
    void updateFile(QFile*);
    void search(std::string, std::string*);
    LinkedList<std::string>* listAllWords();
    void searchSentence(LinkedList<std::string>*, std::string*);

private:
    AVLTST *tst;
    StopWords *stopWords;
    FileHolder *fileHolder;
    bool contains(LinkedList<CustomFile*> *customFiles, CustomFile *customFile);

};

#endif // TSTWRAPPER_H
