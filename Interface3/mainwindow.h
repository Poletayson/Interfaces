#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
