#include "prefixtree.h"
#include <iostream>
#include <QVector>
#include <QString>
#include <assert.h>
#include <QCoreApplication>
#include <QApplication>
#include "mainwindow.h"
using namespace std;

 enum level { back, returning, restart, start, go, finish};
void testKonstr() {

    PrefixTree<QString, enum level> tree;
    QString n = "MISUA";
    QString ss = "MISHA";
    assert(tree.getCountKeys() == 0);
    tree.add(n, back);
    tree.add(ss, returning);
    assert(tree.getCountKeys() == 2);
}

void testDelKey() {
    PrefixTree<QString, enum level> tree;
    QString n = "MISUA";
    QString ss = "MISHA";
    tree.add(n, returning);
    tree.add(ss, start);
    tree.add(ss, start);
    tree.delkey(ss);
    assert(tree.getCountKeys() == 1);
}



void testDelAll() {
    PrefixTree<QString, enum level> tree;
    QString n = "MISUA";
    QString ss = "MISHA";
    tree.add(n, returning);
    tree.add(ss, start);
    tree.delAll();
    assert(tree.getCountKeys() == 0);
}


void testGetValue() {
    PrefixTree<QString, enum level> tree;
    QString n = "MISUA";
    QString ss = "MISHA";
    tree.add(n, finish);
    tree.add(ss, go);
    assert(tree[ss] == go);


}

void testDeleteAllEqual() {
    PrefixTree<QString, enum level> tree;
    PrefixTree<QString, enum level> tree2;
    QString n = "MISUA";
    QString ss = "MISHA";
    tree.add(n, go);
    tree.add(ss, finish);
    tree.delAll();
    assert(tree == tree2);
}

void testKostrCopy() {
    PrefixTree<QString, enum level> tree;
    QString n = "MISUA";
    QString ss = "MISHA";
    tree.add(n, go);
    tree.add(ss, finish);
    PrefixTree<QString, enum level> tree2(tree);
    assert(tree == tree2);
}


void testFile() {

    PrefixTree<QString, enum level> tree;
    PrefixTree<QString, enum level> log;
    QString n = "MISUA";
    QString ss = "MISHA";
    tree.add(n, go);
    tree.add(ss, finish);
    tree.add(ss, go);
    QString name = "filenames.lab";
    tree.saveFile(name);
    log.loadFile(name);

    assert(tree == log);
}


void testIsKey() {

    PrefixTree<QString, enum level> tree;
    PrefixTree<QString, enum level> log;
    QString n = "MISUA";
    QString ss = "MISHA";
    tree.add(n, go);
    tree.add(ss, finish);
    tree.add(ss, go);
    assert( tree.isKey(ss) == true);
    tree.delkey(ss);
    assert( tree.isKey(ss) == false);

}

void tests()
{
    testKonstr();
    testDelKey();
    testDelAll();
    testGetValue();
    testDeleteAllEqual();
    testKostrCopy();
    testFile();
    testIsKey();
}




int main(int argc, char *argv[])
{
    tests();
    cout << "All tests pased" << endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Laba");
    w.show();
    return a.exec();
}


