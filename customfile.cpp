#include "customfile.h"

using namespace std;

CustomFile::CustomFile() {}

void CustomFile::setFileName(std::string fileName) {
    this->fileName = fileName;
}

void CustomFile::setFilePath(std::string filePath) {
    this->filePath = filePath;
}

void CustomFile::addIndex(int index) {
    this->startIndexes.push_back(index);
}

std::string CustomFile::getFileName() {
    return this->fileName;
}

std::string CustomFile::getFilePath() {
    return this->filePath;
}

std::vector<int> CustomFile::getIndexes() {
    return this->startIndexes;
}
