#ifndef WORD_H
#define WORD_H

#include <string>
#include <customfile.h>

class Word {

public:
    Word(string, CustomFile);
    Word(string);
    Word();
    void setText(string);
    string getText();
    void setCustomFile(CustomFile);
    CustomFile getCustomFile();

private:
    string text;
    CustomFile customFile;

};

#endif // WORD_H
