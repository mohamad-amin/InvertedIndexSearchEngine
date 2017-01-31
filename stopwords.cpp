#include "stopwords.h"
#include <QDebug>

StopWords::StopWords() {}

void StopWords::addStopWords(QFile *file) {

    FileProcessor processor(file);
    QStringList *words = processor.getWordsFromFile();

    for (int i=0; i<words->size(); i++) {
        this->trie.add(words->at(i).toStdString().c_str());
    }

}

bool StopWords::has(std::string word) {

    return this->trie.get(word.c_str()) != NULL;

}
