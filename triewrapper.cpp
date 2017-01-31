#include "triewrapper.h"
#include <qdebug.h>
#include <QDir>

TrieWrapper::TrieWrapper(StopWords *stopWords, FileHolder *fileHolder) {
    this->trie = new Trie;
    this->stopWords = stopWords;
    this->fileHolder = fileHolder;
}

bool isWordTrie(QString text) {
    for (int i=0; i<text.length(); i++) {
        if (text.at(i).toLatin1() < 'a' || text.at(i).toLatin1() > 'z') {
            return false;
        }
    }
    return true;
}

int TrieWrapper::getCount() {
    return trie->traverse()->getSize();
}

void TrieWrapper::addFile(QFile *file, int dirLength) {

    FileProcessor *processor = new FileProcessor(file);
    QStringList *list = processor->getWordsFromFile();

    std::string fileName = file->fileName().toStdString();
    std::string filePath = fileName.substr(dirLength);

    for (int i=0; i<list->size(); i++) {
        if (!isWordTrie(list->at(i))) {
            continue;
        }
        if (stopWords->has(list->at(i).toStdString())) {
            continue;
        }
        TrieNodePointer node = trie->add(list->at(i).toStdString().c_str());
        if (node) {

            LinkedList<CustomFile*> *customFiles = node->list;
            CustomFile *customFile;

            if (node->list->getSize() > 0) {
                customFile = node->list->get(node->list->getSize()-1);
                if (customFile && customFile->getFileName() == fileName) {
                    customFile->addIndex(i);
                } else {
                    customFile = new CustomFile;
                    customFile->setFileName(fileName);
                    customFile->setFilePath(filePath);
                    customFile->addIndex(i);
                    node->list->add(customFile);
                }
            } else {
                customFile = new CustomFile;
                customFile->setFileName(fileName);
                customFile->setFilePath(filePath);
                customFile->addIndex(i);
                node->list->add(customFile);
            }

        } else {
            qDebug() << "TrieWrapper adding trie returned NULL :|";
        }
    }
}

void TrieWrapper::removeFile(QFile *file) {

    FileProcessor *processor = new FileProcessor(file);
    QStringList *list = processor->getWordsFromFile();

    for (int i=0; i<list->size(); i++) {

        TrieNodePointer node = trie->get(list->at(i).toStdString().c_str());
        if (node) {
            LinkedList<CustomFile*> *customFiles = node->list;
            for (int j=0; j<customFiles->getSize(); j++) {
                if (customFiles->get(j)->getFileName() == file->fileName().toStdString()) {
                    customFiles->remove(j);
                    qDebug() << "Removing " << list->at(i) << " from trie node's custom files";
                    break;
                }
            }
            if (customFiles->getSize() < 1) {
                qDebug() << "Removing trie ndoe: " << list->at(i);
                trie->remove(list->at(i).toStdString().c_str());
            }
        }

    }

}

void TrieWrapper::updateFile(QFile *file) {

    LinkedList<TrieNode> *nodes = trie->traverse();

    for (int i=0; i<nodes->getSize(); i++) {

        LinkedList<CustomFile*> *customFiles = nodes->get(i).list;

        for (int j=0; j<customFiles->getSize(); j++) {

            if (customFiles->get(j)->getFileName() == file->fileName().toStdString()) {

                qDebug() << "Removing file " << file->fileName() << " from trie node for update";
                customFiles->remove(j);
                if (customFiles->getSize() < 1) {
                    qDebug() << "No other files were attached to this trie node, gonna remove it too";
                    trie->remove(nodes->get(i).word->c_str());
                    break;
                }
            }
        }

    }

    addFile(file, nodes->get(0).list->get(0)->getFileName().length() -
            nodes->get(0).list->get(0)->getFileName().length());

}

LinkedList<std::string>* TrieWrapper::listAllWords() {

    LinkedList<std::string>* words = new LinkedList<std::string>;
    LinkedList<TrieNode> *nodes = trie->traverse();

    for (int i=0; i<nodes->getSize(); i++) {

        if (nodes->get(i).list->getSize() > 0) {

            std::string result = *(nodes->get(i).word) + " ";
            for (int j=0; j<nodes->get(i).list->getSize(); j++) {
                result += nodes->get(i).list->get(j)->getFilePath() + ", ";
            }
            words->add(result);

        }

    }

    return words;

}
bool TrieWrapper::contains(LinkedList<CustomFile*> *customFiles, CustomFile *customFile) {
    for (int i=0; i<customFiles->getSize(); i++) {
        if (customFiles->get(i)->getFileName() == customFile->getFileName() && customFiles->get(i)->getFilePath() == customFile->getFilePath()) {
            return true;
        }
    }
    return false;
}

void TrieWrapper::searchSentence(LinkedList<std::string> *list, std::string *result) {

    LinkedList<TrieNodePointer> *nodes = new LinkedList<TrieNodePointer>;
    TrieNodePointer node;
    for (int i=0; i<list->getSize(); i++) {
        node = trie->get(list->get(i).c_str());
        if (node) {
            nodes->add(node);
        }
    }

    LinkedList<CustomFile*> *customFiles = new LinkedList<CustomFile*>;

    for (int i=0; i<nodes->getSize(); i++) {
        node = nodes->get(i);
        if (node && node->list) {
            for (int i=0; i<node->list->getSize(); i++) {
                customFiles->add(node->list->get(i));
            }
        }
    }

    for (int i=0; i<nodes->getSize(); i++) {
        node = nodes->get(i);
        for (int j=0; j<customFiles->getSize(); j++) {
            if (!contains(node->list, customFiles->get(j))) {
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

void TrieWrapper::search(std::string word, std::string *result) {

    TrieNodePointer node = trie->get(word.c_str());
    if (node && node->list->getSize() > 0) {

        for (int i=0; i<node->list->getSize(); i++) {
            *result = node->list->get(i)->getFilePath();
            *result += " : ";
            for (int i : node->list->get(i)->getIndexes()) {
                *result += std::to_string(i);
                *result += ", ";
            }
            *result += "\n";
        }

    } else {
        *result = "Nothing found :(";
    }

}
