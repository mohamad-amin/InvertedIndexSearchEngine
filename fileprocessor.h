#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <QFile>
#include <string>
#include <linkedlist.h>

class FileProcessor {

public:
    FileProcessor();
    FileProcessor(QFile *file) : file(file) {}
    QStringList* getWordsFromFile();
    void setFile(QFile *file) {
        this->file = file;
    }

private:
    QFile *file;

    QStringList *tokenizeText(std::string);

};

#endif // FILEPROCESSOR_H
