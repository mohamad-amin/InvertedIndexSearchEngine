#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <sstream>
#include <qdebug.h>

void MainWindow::initializeTrees() {
    this->bstWrapper = new BSTWrapper(this->stopWords, this->fileHolder);
    this->tstWrapper = new TSTWrapper(this->stopWords, this->fileHolder);
    this->trieWrapper = new TrieWrapper(this->stopWords, this->fileHolder);
    this->hashMapWrapper = new HashMapWrapper(this->stopWords, this->fileHolder);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->fileHolder = new FileHolder;
    this->stopWords = new StopWords;
    stopWords->addStopWords(new QFile(QString("/home/mohamadamin/StopWords.txt")));
    initializeTrees();
}

std::string replaceAllA(std::string text, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = text.find(from, start_pos)) != std::string::npos) {
        text.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return text;
}

void trimStringSpacingA(std::string &text) {
    text = replaceAllA(text, "\n\n\n", " ");
    text = replaceAllA(text, "\n\n", " ");
    text = replaceAllA(text, "\n", " ");
    while (text.find("  ") != std::string::npos) {
        text = replaceAllA(text, "  ", " ");
    }
}

LinkedList<std::string>* tokenizeText(std::string text) {
    trimStringSpacingA(text);
    LinkedList<std::string> *list = new LinkedList<std::string>;
    std::stringstream stream(text);
    std::string buffer;
    while (stream >> buffer) {
        list->add(buffer);
    }
    return list;
}


MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::buildTrees(QString dirName) {
    QDir myDir(dirName);
    QStringList allFiles = myDir.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    for (QString str : allFiles) {
        if (QDir(dirName + str).exists()) {
            buildTrees(dirName + QString("/") + str);
        }
        QFile *file = new QFile(dirName + QString("/") + str);
        fileHolder->addFile(file);
        if (ui->bst->isChecked()) {
            this->bstWrapper->addFile(file, this->dir.length());
        } else if (ui->tst->isChecked()) {
            this->tstWrapper->addFile(file, this->dir.length());
        } else if (ui->trie->isChecked()) {
            this->trieWrapper->addFile(file, this->dir.length());
        } else if (ui->hashMap->isChecked()) {
            this->hashMapWrapper->addFile(file, this->dir.length());
        }
    }
}

void MainWindow::on_build_clicked() {
    buildTrees(this->dir);
}

void MainWindow::on_browse_clicked() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Directory"),
                                                    "/home/mohamadamin/docs",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    ui->folderEdit->setText(dir);
    this->dir = dir;
}

void MainWindow::listAllWords() {
    LinkedList<std::string> *words;
    if (ui->bst->isChecked()) {
        words = bstWrapper->listAllWords();
    } else if (ui->tst->isChecked()) {
        words = tstWrapper->listAllWords();
    } else if (ui->trie->isChecked()) {
        words = trieWrapper->listAllWords();
    } else if (ui->hashMap->isChecked()) {
        words = this->hashMapWrapper->listAllWords();
    }
    for (int i=0; i<words->getSize(); i++) {
        ui->result->append(QString(words->get(i).c_str()));
    }
    ui->result->append("\n");
    ui->result->append("Number of words: ");
    ui->result->append(QString::number(words->getSize()));
}

int MainWindow::listAllFiles(bool first) {

    QVector<QFile*> files = fileHolder->getAllFiles();
    int i;
    for (i=0; i<files.size(); i++) {
        ui->result->append(files.at(i)->fileName());
    }

    if (first) {
        ui->result->append("\nTotal number of files: ");
        ui->result->append(QString::number(i));
    }

}

void MainWindow::listFilesInThisFolder() {
    QDir myDir(this->dir);
    int i=0;
    ui->result->clear();
    QStringList allFiles = myDir.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    for (QString str : allFiles) {
        i++;
        QFile *file = new QFile(str);
        ui->result->append(file->fileName());
    }
    ui->result->append("\nTotal number of files: ");
    ui->result->append(QString::number(i));
}

void MainWindow::addFile(std::string fileName) {
    if (ui->bst->isChecked()) {
        bstWrapper->addFile(new QFile(QString(fileName.c_str())), this->dir.length());
    } else if (ui->tst->isChecked()) {
        tstWrapper->addFile(new QFile(QString(fileName.c_str())), this->dir.length());
    } else if (ui->trie->isChecked()) {
        trieWrapper->addFile(new QFile(QString(fileName.c_str())), this->dir.length());
    } else if (ui->hashMap->isChecked()) {
        this->hashMapWrapper->addFile(new QFile(QString(fileName.c_str())), this->dir.length());
    }
    ui->result->clear();
    ui->result->append("Successful :D");
}

void MainWindow::updateFile(std::string fileName) {
    if (ui->bst->isChecked()) {
        bstWrapper->updateFile(new QFile(QString(fileName.c_str())));
    } else if (ui->tst->isChecked()) {
        tstWrapper->updateFile(new QFile(QString(fileName.c_str())));
    } else if (ui->trie->isChecked()) {
        trieWrapper->updateFile(new QFile(QString(fileName.c_str())));
    } else if (ui->hashMap->isChecked()) {
        hashMapWrapper->updateFile(new QFile(QString(fileName.c_str())));
    }
    ui->result->clear();
    ui->result->append("Successful :D");
}

void MainWindow::deleteFile(std::string fileName) {
    fileHolder->removeFile(new QFile(QString(fileName.c_str())));
    if (ui->bst->isChecked()) {
        bstWrapper->removeFile(new QFile(QString(fileName.c_str())));
    } else if (ui->tst->isChecked()) {
        tstWrapper->removeFile(new QFile(QString(fileName.c_str())));
    } else if (ui->trie->isChecked()) {
        trieWrapper->removeFile(new QFile(QString(fileName.c_str())));
    } else if (ui->hashMap->isChecked()) {
        hashMapWrapper->removeFile(new QFile(QString(fileName.c_str())));
    }
    ui->result->clear();
    ui->result->append("Successful :D");
}

void MainWindow::searchWord(std::string word) {
    std::string *result = new std::string;
    qDebug() << "Gonna search";
    if (ui->bst->isChecked()) {
        bstWrapper->search(word, result);
    } else if (ui->tst->isChecked()) {
        tstWrapper->search(word, result);
    } else if (ui->trie->isChecked()) {
        trieWrapper->search(word, result);
    } else if (ui->hashMap->isChecked()) {
        hashMapWrapper->search(word, result);
    }
    qDebug() << "result : " << (*result).c_str();
    ui->result->clear();
    ui->result->append(QString((*result).c_str()));
}

void MainWindow::searchSentence(LinkedList<std::string>* sentence) {
    std::string *result = new std::string;
    if (ui->bst->isChecked()) {
        bstWrapper->searchSentence(sentence, result);
    } else if (ui->tst->isChecked()) {
        tstWrapper->searchSentence(sentence, result);
    } else if (ui->trie->isChecked()) {
        trieWrapper->searchSentence(sentence, result);
    } else if (ui->hashMap->isChecked()) {
        hashMapWrapper->searchSentence(sentence, result);
    }
    ui->result->clear();
    ui->result->append(QString((*result).c_str()));
}

void MainWindow::on_command_returnPressed() {
    LinkedList<std::string>* command = tokenizeText(this->ui->command->text().toLower().toStdString());
    if (command->get(0) == "add") {
        this->addFile(command->get(1));
    } else if (command->get(0) == "del") {
        this->deleteFile(command->get(1));
    } else if (command->get(0) == "update") {
        this->updateFile(command->get(1));
    } else if (command->get(0) == "list") {
        if (command->get(1) == "-w") {
//            qDebug() << "trie: " << trieWrapper->getCount();
            listAllWords();
        } else if (command->get(1) == "-l") {
            listAllFiles(true);
        } else if (command->get(1) == "-f") {
            listFilesInThisFolder();
        }
    } else if (command->get(0) == "search") {
        if (command->get(1) == "-w") {
            searchWord(command->get(2));
        } else if (command->get(1) == "-s") {
            command->remove(0);
            command->remove(1);
            searchSentence(command);
        }
    }
}
