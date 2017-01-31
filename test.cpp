// Created by mohamadamin on 1/10/17.

#include "iostream"
#include "avltst.h"

int xmain() {

    AVLTST tst;
    tst.add("hello"); // 7
    tst.add("hello"); // 7
    tst.add("this"); // 11
    tst.add("is"); // 9
    tst.add("me"); // 10
    tst.add("from"); // 5
    tst.add("here"); // 11
    tst.add("a"); // 6
    tst.add("aasd"); // 1
    tst.add("aasd"); // 1
    tst.add("aasda"); // 2
    tst.add("aqweq");
    tst.add("aqweq");
    tst.add("aqwzxe"); // 4
    tst.add("aadgsd"); // 0
    tst.add("aqwec"); // 3
    tst.add("hellox"); // 7
    tst.add("hellox"); // 7
    tst.add("thisx"); // 11
    tst.add("isx"); // 9
    tst.add("mex"); // 10
    tst.add("fromx"); // 5
    tst.add("herex"); // 11
    tst.add("ax"); // 6
    tst.add("aasdx"); // 1
    tst.add("aasdx"); // 1
    tst.add("aasdax"); // 2
    tst.add("aqweqx");
    tst.add("aqweqx");
    tst.add("aqwzxex"); // 4
    tst.add("aadgsdx"); // 0
    tst.add("aqwecx"); // 3

//    std::cout << "printing list:" << std::endl;

//    int i=0;
//    while (tst.getSize()) {
//        std::cout << "Item " << i++ << ": " << tst.pop() << " and before it: " << tst.getBefore() << std::endl;
//    }

//    tst.remove(7);
//    std::cout << "printing list after removing a: " << std::endl;
//    for (int i=0; i<tst.getSize(); i++) {
//        std::cout << "item " << i << ": " << tst.get(i) << std::endl;
//    }

//    std::cout << "Retest - printing 0 to 6" << std::endl;
//    for (int i=0; i<7; i++) {
//        std::cout << "item " << i << ": " << tst.get(i) << std::endl;
//    }
//    std::cout << "removing 4 to see what happens" << std::endl;
//    tst.remove(4);
//    std::cout << "printing list from 6 to size-1" << std::endl;
//    for (int i=6; i<tst.getSize(); i++) {
//        std::cout << "item " << i << ": " << tst.get(i) << std::endl;
//    }

//    std::cout << "again printing them all" << std::endl;
//    for (int i=0; i<tst.getSize(); i++) {
//        std::cout << "item " << i << ": " << tst.get(i) << std::endl;
//    }

    std::cout << "printing tst: " << std::endl;
    LinkedList<AVLTSTNode> *list = tst.traverse();
    std::cout << "size: " << list->getSize() << std::endl;
    for (int i=0; i<list->getSize(); i++) {
        std::cout << "item " << i << ": " << *list->get(i).word << std::endl;
    }

    tst.remove("is");
    std::cout << "printing tst after removing is: " << std::endl;
    list = tst.traverse();
    for (int i=0; i<list->getSize(); i++) {
        std::cout << "item " << i << ": " << *list->get(i).word << std::endl;
    }

    std::cout << "tst has a? " << (bool) (tst.get("a") != NULL) << std::endl;
    std::cout << "tst has good? " << (bool) (tst.get("good") != NULL) << std::endl;
    std::cout << "tst has men? " << (bool) (tst.get("men") != NULL) << std::endl; // here
    std::cout << "tst has hello? " << (bool) (tst.get("hello") != NULL) << std::endl;
    std::cout << "tst has aqwe? " << (bool) (tst.get("aqwe") != NULL) << std::endl;
    std::cout << "tst has m? " << (bool) (tst.get("m") != NULL) << std::endl;
    std::cout << "tst has heree? " << (bool) (tst.get("heree") != NULL) << std::endl;
    std::cout << "tst has hereee? " << (bool) (tst.get("hereee") != NULL) << std::endl;
    std::cout << "tst has aa? " << (bool) (tst.get("aa") != NULL) << std::endl;
    std::cout << "tst has ab? " << (bool) (tst.get("ab") != NULL) << std::endl;
    std::cout << "tst has aqweq? " << (bool) (tst.get("aqweq") != NULL) << std::endl;
    std::cout << "tst has is? " << (bool) (tst.get("is") != NULL) << std::endl;

    return EXIT_SUCCESS;

}
