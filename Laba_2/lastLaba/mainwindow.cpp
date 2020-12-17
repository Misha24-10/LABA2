#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < funcNames.size();i++) {
        ui->comboBox->addItem(funcNames[i]);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    QString fname = ui->comboBox->currentText();
    QString name = ui->lineEdit->text();
    if (name != ""){
        std::string fname_utf8 = fname.toUtf8().constData();
        QString name = ui->lineEdit->text();
        tree.add(name, fname);
        cout << tree.getCountKeys() << endl;
        cout << tree.getCountNodes() << endl;



        QVector<K> vectname = {};
        vectname = tree.getKeys("");


        for (int i = 0; i < vectname.size();i++) {
            cout << vectname[i].toUtf8().constData() << endl;
        }

    }
    drow();
}





void MainWindow::drow() {
    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->header()->setVisible(true);
    ui->treeWidget->headerItem()->setData(0, 0, "Key");
    ui->treeWidget->headerItem()->setData(1, 0, "Function");
    QTreeWidgetItem* item = new QTreeWidgetItem;
    item->setData(0, 0, "");
    item->setData(0, 0x100, " ");
    item->setFlags(Qt::ItemIsEnabled);
    ui->treeWidget->insertTopLevelItem(0, item);

    QString vect  = {};
    auto keys = tree.getKeys(vect);
    auto colorlist_local = keys;

    for (auto key: keys) {
        //Добавление ключа
        QTreeWidgetItem* t = item;
        if (t->text(1).isEmpty())
            t->setFlags(Qt::ItemIsEnabled);
        t->setExpanded(true);
        int child_number = t->childCount();

        for (int j = 0; j<t->childCount(); j++)
            if (t->child(j)->data(0, 0).toString() == key) {
                child_number = j;
                break;
            }
        QTreeWidgetItem* key_item = new QTreeWidgetItem(t);
        QString ss = key;

        key_item->setData(0, 0,  key);
        t->addChild(key_item);
        QTreeWidgetItem* PASS = new QTreeWidgetItem(key_item);
        PASS->setData(0, 0, tree[key]);

        t->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        t->setData(1, 0, "");
    }
}

void MainWindow::on_open_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open", ".", "LAB (*.lab)");
        if (!filename.isEmpty()) {
            if (!filename.endsWith(".lab"))
                QMessageBox::critical(this, "Ошибка", "Неверный формат!");
            else if (!tree.loadFile(filename))
                QMessageBox::critical(this, "Ошибка", "Ошибка при чтении данных! Неверно созданный файл");
        }
        drow();
}

void MainWindow::on_save_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save", ".", "(*.lab)");
            if (not filename.isEmpty()) {
                if (tree.getCountKeys() && filename.endsWith(".lab")) {
                    if (!tree.saveFile(filename)) {
                        QMessageBox::warning(this, "Предупреждение", "Что-то пошло не так");
                    }
                }
                else if (!filename.endsWith(".lab"))
                    QMessageBox::critical(this, "Ошибка", "Неверный формат!");
                else
                    QMessageBox::critical(this, "Ошибка", "Дерево пустое!");
            }
}

void MainWindow::on_program_info_triggered()
{
    QMessageBox::information(this, "Выполнил", "Работу выполнил Яковлев Михаил");
}

void MainWindow::on_pushButton_2_clicked()
{
    tree.delAll();
    drow();
}

void MainWindow::on_pushButton_3_clicked()
{
   QString name = ui->lineEdit_2->text();
   if (name != "") {
       QVector<QString>  treeKeys  = tree.getKeys({});
       if ( treeKeys.count(name) != 0 ) {
           tree.delkey(name);
           drow();
       }
       else {
           QMessageBox::information(this, "Внимание", "Нет такого ключа");
       }
   }
   else {
       QMessageBox::information(this, "Внимание", "Нет такого ключа");
   }
}
