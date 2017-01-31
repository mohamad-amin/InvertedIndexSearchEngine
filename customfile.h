#ifndef CUSTOMFILE_H
#define CUSTOMFILE_H

#include <vector>
#include <string>

class CustomFile {

public:
    CustomFile();
    CustomFile(std::string fileName, std::string filePath) :fileName(fileName), filePath(filePath) {}
    void setFileName(std::string fileName);
    void setFilePath(std::string filePath);
    void addIndex(int index);
    std::string getFileName();
    std::string getFilePath();
    std::vector<int> getIndexes();

private:
    std::string fileName, filePath;
    std::vector<int> startIndexes;

};

#endif // CUSTOMFILE_H
