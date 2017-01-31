#ifndef FILEHOLDER_H
#define FILEHOLDER_H

#include <QFile>
#include <QVector>
#include <QFileInfo>
#include <QDir>

class FileHolder {

public:

    FileHolder();

    QFile* getFile(std::string fileName, std::string filePath) {
        for (int i=0; i<files.size(); i++) {
            if (files.at(i)->fileName().toStdString() == fileName) {
                return files.at(i);
            }
        }
        return 0;
    }

    QVector<QFile*> getAllFiles() {
        return files;
    }

    void addFile(QFile *file) {
        files.append(file);
    }

    void removeFile(QFile *file) {
        for (int i=0; i<files.size(); i++) {
            if (file->fileName() == files.at(i)->fileName()) {
                files.remove(i);
            }
        }
    }

private:

    QVector<QFile*> files;
    int dirLength;

    std::string getFilePath(QFile *file) {
        return QFileInfo((*file)).dir().absolutePath().toStdString();
    }

};

#endif // FILEHOLDER_H
