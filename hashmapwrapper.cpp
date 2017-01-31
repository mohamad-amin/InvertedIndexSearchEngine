#include "hashmapwrapper.h"
#include <qdebug.h>
#include <QDir>

HashMapWrapper::HashMapWrapper(StopWords *stopWords, FileHolder *fileHolder) : stopWords(stopWords), fileHolder(fileHolder) {
    this->hashMap = new HashMap;
}

bool isWordHash(QString text) {
    for (int i=0; i<text.length(); i++) {
        if (text.at(i).toLatin1() < 'a' || text.at(i).toLatin1() > 'z') {
            return false;
        }
    }
    return true;
}

void HashMapWrapper::addFile(QFile *file, int dirLength) {

    std::string fileName = file->fileName().toStdString();
    std::string filePath = fileName.substr(dirLength);

    FileProcessor *processor = new FileProcessor(file);
    QStringList *list = processor->getWordsFromFile();

    for (int i=0; i<list->size(); i++) {
        if (!isWordHash(list->at(i))) {
            continue;
        }
        std::string item = list->at(i).toStdString();
        if (stopWords->has(item)) {
            continue;
        }
        HashEntry *node = hashMap->add(list->at(i).toStdString().c_str());
        if (node) {

            LinkedList<CustomFile*> *customFiles = node->getValue();
            CustomFile *customFile;

            if (node->getValue()->getSize() > 0) {
                customFile = node->getValue()->get(node->getValue()->getSize()-1);
                if (customFile && customFile->getFileName() == fileName) {
                    customFile->addIndex(i);
                } else {
                    customFile = new CustomFile;
                    customFile->setFileName(fileName);
                    customFile->setFilePath(filePath);
                    customFile->addIndex(i);
                    node->getValue()->add(customFile);
                }
            } else {
                customFile = new CustomFile;
                customFile->setFileName(fileName);
                customFile->setFilePath(filePath);
                customFile->addIndex(i);
                node->getValue()->add(customFile);
            }

        } else {
            qDebug() << "HashMapWrapper adding hashMap returned NULL :|";
        }
    }
}

void HashMapWrapper::removeFile(QFile *file) {

    FileProcessor *processor = new FileProcessor(file);
    QStringList *list = processor->getWordsFromFile();

    for (int i=0; i<list->size(); i++) {

        HashEntry *node = hashMap->get(list->at(i).toStdString().c_str());
        if (node) {
            LinkedList<CustomFile*> *customFilesList = node->getValue();
            CustomFile *customFiles[customFilesList->getSize()];
            customFilesList->getAsArray(customFiles);
            int size = customFilesList->getSize();
            int deleted = 0;
            for (int j=0; j<size; j++) {
                if (customFiles[j]->getFileName() == file->fileName().toStdString()) {
                    node->getValue()->remove(j-deleted);
                    deleted++;
                    qDebug() << "Removing " << list->at(i) << " from hashMap node's custom files";
                    break;
                }
            }
            if (customFilesList->getSize() < 1) {
                qDebug() << "Removing hashMap ndoe: " << list->at(i);
                hashMap->remove(list->at(i).toStdString().c_str());
            }
        }

    }

}

void HashMapWrapper::updateFile(QFile *file) {

    LinkedList<HashEntry*> *nodes = hashMap->traverse();

    for (int i=0; i<nodes->getSize(); i++) {

        LinkedList<CustomFile*> *customFilesList = nodes->get(i)->getValue();
        CustomFile *customFiles[customFilesList->getSize()];
        customFilesList->getAsArray(customFiles);

        int size = customFilesList->getSize();
        int deleted = 0;

        for (int j=0; j<size; j++) {

            if (customFiles[j]->getFileName() == file->fileName().toStdString()) {

                qDebug() << "Removing file " << file->fileName() << " from hashMap node for update";
                customFilesList->remove(j-deleted);
                deleted++;
                if (customFilesList->getSize() < 1) {
                    qDebug() << "No other files were attached to this hashMap node, gonna remove it too";
                    hashMap->remove(nodes->get(i)->getKey()->c_str());
                    break;
                }
            }
        }

    }

    addFile(file, nodes->get(0)->getValue()->get(0)->getFileName().length() -
            nodes->get(0)->getValue()->get(0)->getFileName().length());

}

LinkedList<std::string>* HashMapWrapper::listAllWords() {

    LinkedList<std::string>* words = new LinkedList<std::string>;
    LinkedList<HashEntry*> *nodes = hashMap->traverse();

    for (int i=0; i<nodes->getSize(); i++) {

        if (nodes->get(i)->getValue()->getSize() > 0) {

            std::string result = *(nodes->get(i)->getKey()) + " ";
            for (int j=0; j<nodes->get(i)->getValue()->getSize(); j++) {
                result += nodes->get(i)->getValue()->get(j)->getFilePath() + ", ";
            }
            words->add(result);

        }

    }

    return words;

}

bool contains(LinkedList<CustomFile*> *customFiles, CustomFile *customFile) {
    for (int i=0; i<customFiles->getSize(); i++) {
        if (customFiles->get(i)->getFileName() == customFile->getFileName() && customFiles->get(i)->getFilePath() == customFile->getFilePath()) {
            return true;
        }
    }
    return false;
}

void HashMapWrapper::searchSentence(LinkedList<std::string> *list, std::string *result) {

    LinkedList<HashEntry*> *nodes = new LinkedList<HashEntry*>;
    for (int i=0; i<list->getSize(); i++) {
        HashEntry *node = hashMap->get(list->get(i).c_str());
        if (node) {
            nodes->add(node);
        }
    }

    LinkedList<CustomFile*> *customFiles = new LinkedList<CustomFile*>;

    HashEntry* node;
    for (int i=0; i<nodes->getSize(); i++) {
        node = nodes->get(i);
        if (node && node->getValue()) {
            for (int i=0; i<node->getValue()->getSize(); i++) {
                customFiles->add(node->getValue()->get(i));
            }
        }
    }

    for (int i=0; i<nodes->getSize(); i++) {
        node = nodes->get(i);
        for (int j=0; j<customFiles->getSize(); j++) {
            if (!contains(node->getValue(), customFiles->get(j))) {
                customFiles->remove(j);
                if (customFiles->getSize() == 0) {
                    *result = "Nothing found :(";
                    return;
                }
                continue;
            }
        }
    }

    bool has = false;

    for (int i=0; i<customFiles->getSize(); i++) {
        CustomFile *customFile = customFiles->get(i);
        (*result) += customFile->getFileName() + " |->\n";
        has = true;
        FileProcessor proc;
        proc.setFile(this->fileHolder->getFile(customFile->getFileName(), customFile->getFilePath()));
        QStringList *words = proc.getWordsFromFile();
        for (int j=0; j<customFile->getIndexes().size(); j++) {
            *result += "\t";
            int index = customFile->getIndexes().at(j);
            if (index < 1) {
                *result += words->at(index).toStdString() + " " + words->at(index+1).toStdString() + " ... ";
            } else if (index < 2) {
                *result += words->at(index-1).toStdString() + " " + words->at(index).toStdString() + " " + words->at(index+1).toStdString() + " ... ";
            } else if (index < words->size()-2) {
                *result += " ... " + words->at(index-1).toStdString() + " " + words->at(index).toStdString() + " " + words->at(index+1).toStdString() + " ... ";
            } else if (index < words->size()-1) {
                *result += " ... " + words->at(index-1).toStdString() + " " + words->at(index).toStdString() + " " + words->at(index+1).toStdString();
            } else {
                *result += " ... " + words->at(index-1).toStdString() + " " + words->at(index).toStdString();
            }
            *result += "\n";
        }
        *result += "\n\n";
    }

    if (!has) {
        *result = "Nothing found :(";
    }

}

void HashMapWrapper::search(std::string word, std::string *result) {

    HashEntry *node = this->hashMap->get(word.c_str());
    if (node && node->getValue()->getSize() > 0) {

        for (int i=0; i<node->getValue()->getSize(); i++) {
            *result = node->getValue()->get(i)->getFilePath();
            *result += " : ";
            for (int i : node->getValue()->get(i)->getIndexes()) {
                *result += std::to_string(i);
                *result += ", ";
            }
            *result += "\n";
        }

    } else {
        *result = "Nothing found :(";
    }

}
