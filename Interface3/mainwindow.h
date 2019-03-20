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
    //Добавить строку в конец
    void addRow ();

private slots:
    void productClicked(int pos);
    void edinClicked(int pos);
public slots:
    void Save ();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
