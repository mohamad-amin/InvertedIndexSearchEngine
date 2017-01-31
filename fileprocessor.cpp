#include "fileprocessor.h"
#include <QStringList>
#include <QDebug>

FileProcessor::FileProcessor() {}

QStringList* FileProcessor::getWordsFromFile() {
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QString text(file->readAll().toLower());
    QStringList temp = text.split(QRegExp("\\W+"), QString::SkipEmptyParts);
    QStringList *list = new QStringList(temp);
    file->close();
    return list;
}
