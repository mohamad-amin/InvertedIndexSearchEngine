#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stopwords.h>
#include <bstwrapper.h>
#include <tstwrapper.h>
#include <fileholder.h>
#include <triewrapper.h>
#include <hashmapwrapper.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_build_clicked();

    void on_browse_clicked();

    void on_command_returnPressed();

private:
    QString dir;
    Ui::MainWindow *ui;
    StopWords *stopWords;
    BSTWrapper *bstWrapper;
    TSTWrapper *tstWrapper;
    TrieWrapper *trieWrapper;
    HashMapWrapper *hashMapWrapper;
    FileHolder *fileHolder;

    void initializeTrees();
    void buildTrees(QString dirName);

    void listAllWords();
    int listAllFiles(bool);
    void listFilesInThisFolder();
    void addFile(std::string fileName);
    void updateFile(std::string fileName);
    void deleteFile(std::string fileName);
    void searchWord(std::string word);
    void searchSentence(LinkedList<std::string>* sentence);

};

#endif // MAINWINDOW_H
