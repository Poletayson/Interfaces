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
    ///Записываем доптаблицу в форму в допстолбец n
    void dopTableToExel (int n, QTableWidget* table, QXlsx::Document* form, QDateEdit* Date);

private slots:
    void productClicked(int pos);
    void edinClicked(int pos);
    void on_tableWidget_cellChanged(int row, int column);
    ///изменилась вкладка
    void on_tabWidget_currentChanged(int index);

    void on_tableWidget_2_cellChanged(int row, int column);

    void on_tableWidget_3_cellChanged(int row, int column);

    void on_tableWidget_4_cellChanged(int row, int column);

    void on_tableWidget_5_cellChanged(int row, int column);

public slots:
    void Save ();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
