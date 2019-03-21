#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
//#include <
#include <xlsxdocument.h>   //библиотека для Exel
#include <xlsxformat.h>



#include <businesslogic.h>
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    BusinessLogic BL;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ///Добавить строку в конец таблицы n (с единицы)
    void addRow (int n);

private slots:
    void productClicked(int pos);
    void edinClicked(int pos);
    void on_tableWidget_cellChanged(int row, int column);
    ///изменилась вкладка
    void on_tabWidget_currentChanged(int index);

public slots:
    void Save ();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
