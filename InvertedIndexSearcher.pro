#-------------------------------------------------
#
# Project created by QtCreator 2016-12-01T01:00:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InvertedIndexSearcher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customfile.cpp \
    tst.cpp \
    trie.cpp \
    bstwrapper.cpp \
    fileprocessor.cpp \
    tstwrapper.cpp \
    triewrapper.cpp \
    stopwords.cpp \
    test.cpp \
    hashmap.cpp \
    hashmapwrapper.cpp \
    avltst.cpp \
    fileholder.cpp

HEADERS  += mainwindow.h \
    customfile.h \
    linkedlist.h \
    bst.h \
    tst.h \
    trie.h \
    bstwrapper.h \
    fileprocessor.h \
    linkedlist.hpp \
    tstwrapper.h \
    triewrapper.h \
    bst.hpp \
    stopwords.h \
    hashmap.h \
    hashmapwrapper.h \
    avl.h \
    stack.h \
    stack.hpp \
    avl.hpp \
    avltst.h \
    fileholder.h

FORMS    += mainwindow.ui
