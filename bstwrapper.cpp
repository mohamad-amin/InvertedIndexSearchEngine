#include "bstwrapper.h"
#include <qdebug.h>
#include <QDir>
#include <QString>

BSTWrapper::BSTWrapper(StopWords *stopWords, FileHolder *fileHolder) {
    this->bst = new AVL<std::string>;
    this->stopWords = stopWords;
    this->fileHolder = fileHolder;
}

bool isWordBst(QString text) {
    for (int i=0; i<text.length(); i++) {
        if (text.at(i).toLatin1() < 'a' || text.at(i).toLatin1() > 'z') {
            return false;
        }
    }
    return true;
}

void BSTWrapper::addFile(QFile *file, int dirLength) {

    std::string fileName = file->fileName().toStdString();
    std::string filePath = fileName.substr(dirLength);

    FileProcessor *processor = new FileProcessor(file);
    QStringList *list = processor->getWordsFromFile();

    for (int i=0; i<list->size(); i++) {
        QString str = list->at(i);
        if (!isWordBst(list->at(i))) {
            continue;
        }
        std::string item = str.toStdString();
        if (stopWords->has(item)) {
            continue;
        }
        AVLNode<std::string> *node = bst->add(item);
        if (node) {
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
            qDebug() << "BSTWRapper adding bst returned NULL :|" << item.c_str();
        }
    }

}

void BSTWrapper::removeFile(QFile *file) {

    FileProcessor *processor = new FileProcessor(file);
    QStringList *list = processor->getWordsFromFile();

    for (int i=0; i<list->size(); i++) {

        AVLNode<std::string> *node = bst->get(list->at(i).toStdString());
        if (node) {
            LinkedList<CustomFile*> *customFilesList = node->list;
            CustomFile *customFiles[customFilesList->getSize()];
            customFilesList->getAsArray(customFiles);
            int size = customFilesList->getSize();
            int deleted = 0;
            for (int j=0; j<size; j++) {
                if (customFiles[j]->getFileName() == file->fileName().toStdString()) {
                    node->list->remove(j-deleted);
                    deleted++;
                    qDebug() << "Removing " << list->at(i) << " from BST node's custom files";
                    break;
                }
            }
            if (customFilesList->getSize() < 1) {
                qDebug() << "Removing BST ndoe: " << list->at(i);
                bst->remove(list->at(i).toStdString());
            }
        }

    }

}

void BSTWrapper::updateFile(QFile *file) {

    LinkedList<AVLNode<std::string>> *nodes = bst->getNodesInInorder();

    for (int i=0; i<nodes->getSize(); i++) {

        LinkedList<CustomFile*> *customFilesList = nodes->get(i).list;
        CustomFile *customFiles[customFilesList->getSize()];
        customFilesList->getAsArray(customFiles);

        int size = customFilesList->getSize();
        int deleted = 0;

        for (int j=0; j<size; j++) {

            if (customFiles[j]->getFileName() == file->fileName().toStdString()) {

                qDebug() << "Removing file " << file->fileName() << " from bst node for update";
                customFilesList->remove(j-deleted);
                deleted++;
                if (customFilesList->getSize() < 1) {
                    qDebug() << "No other files were attached to this bst node, gonna remove it too";
                    bst->remove(nodes->get(i).data);
                    break;
                }
            }
        }

    }

    addFile(file, nodes->get(0).list->get(0)->getFileName().length() -
            nodes->get(0).list->get(0)->getFileName().length());

}

LinkedList<std::string>* BSTWrapper::listAllWords() {

    LinkedList<std::string>* words = new LinkedList<std::string>;
    LinkedList<AVLNode<std::string>> *nodes = bst->getNodesInInorder();

    for (int i=0; i<nodes->getSize(); i++) {

        if (nodes->get(i).list->getSize() > 0) {

            std::string result = nodes->get(i).data + " ";
            for (int j=0; j<nodes->get(i).list->getSize(); j++) {
                result += nodes->get(i).list->get(j)->getFilePath() + ", ";
            }
            words->add(result);

        }

    }

    return words;

}

bool BSTWrapper::contains(LinkedList<CustomFile*> *customFiles, CustomFile *customFile) {
    for (int i=0; i<customFiles->getSize(); i++) {
        if (customFiles->get(i)->getFileName() == customFile->getFileName() && customFiles->get(i)->getFilePath() == customFile->getFilePath()) {
            return true;
        }
    }
    return false;
}

void BSTWrapper::searchSentence(LinkedList<std::string> *list, std::string *result) {

    LinkedList<AVLNode<std::string>*> *nodes = new LinkedList<AVLNode<std::string>*>;
    for (int i=0; i<list->getSize(); i++) {
        AVLNode<std::string> *node = bst->get(list->get(i).c_str());
        if (node) {
            nodes->add(node);
        }
    }

    LinkedList<CustomFile*> *customFiles = new LinkedList<CustomFile*>;

    AVLNode<std::string>* node;
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

void BSTWrapper::search(std::string word, std::string *result) {

    *result = "";

    AVLNode<std::string>* node = bst->get(word.c_str());
    if (node && node->list->getSize() > 0) {

        for (int i=0; i<node->list->getSize(); i++) {
            *result += node->list->get(i)->getFilePath();
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
