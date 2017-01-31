#ifndef STOPWORDS_H
#define STOPWORDS_H

#include <trie.h>
#include <fileprocessor.h>

class StopWords {

public:
    StopWords();
    void addStopWords(QFile*);
    bool has(std::string);

private:
    Trie trie;
};

#endif // STOPWORDS_H
