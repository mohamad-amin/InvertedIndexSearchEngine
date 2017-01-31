#include "word.h"

Word::Word() {}

Word::Word(string text) : text(text) {}

Word::Word(string text, CustomFile customFile) : text(text), customFile(customFile) {}

void Word::setText(string text) : text(text) {}

void Word::setCustomFile(CustomFile customFile) : customFile(customFile) {}

string Word::getText() {
    return this->text;
}

CustomFile Word::getCustomFile() {
    return this->customFile;
}
