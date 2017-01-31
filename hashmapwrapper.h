#ifndef HASHMAPWRAPPER_H
#define HASHMAPWRAPPER_H

#include <hashmap.h>
#include <stopwords.h>
#include <fileholder.h>
#include <fileprocessor.h>

class HashMapWrapper {

public:

    HashMapWrapper(StopWords*, FileHolder*);
    void addFile(QFile*, int);
    void removeFile(QFile*);
    void updateFile(QFile*);
    void search(std::string, std::string*);
    LinkedList<std::string>* listAllWords();
    void searchSentence(LinkedList<std::string>*, std::string*);

private:

    HashMap *hashMap;
    StopWords *stopWords;
    FileHolder *fileHolder;

};

#endif // HASHMAPWRAPPER_H
