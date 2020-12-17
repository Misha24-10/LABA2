#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <PrefixTree.h>

typedef QString K;
typedef QString V;
typedef PrefixTree<QString, QString> FuncTree;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<QString> funcNames = {"back", "returning", "restart", "start", "go", "finish"};

private slots:

    void on_pushButton_clicked();

    void on_open_triggered();

    void on_save_triggered();

    void on_program_info_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QVector<K>  vect;
    FuncTree tree;
    void drow();
};
#endif // MAINWINDOW_H
