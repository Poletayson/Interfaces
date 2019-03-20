#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QObject::connect(ui->tableWidget->ite, SIGNAL(itemClicked(QTableWidgetItem *item)), this, SLOT (on_tableWidget_itemActivated(QTableWidgetItem *item)));

    ui->tableWidget->setColumnWidth(0, 250);
    ui->tableWidget->setColumnWidth(1, 100);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 150);
    ui->tableWidget->setColumnWidth(4, 150);
    ui->tableWidget->setColumnWidth(5, 150);
    ui->tableWidget->setColumnWidth(6, 150);


    addRow();
    //устанавливаем запрет на редактирование
    //int c = ui->tableWidget->rowCount()-1;
    QTableWidgetItem* ptr = new QTableWidgetItem();
    Qt::ItemFlags flags = ptr->flags() & ~Qt::ItemFlag::ItemIsEditable;

    ptr->setFlags(flags);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, ptr);

    ptr = new QTableWidgetItem();
    ptr->setFlags(flags);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, ptr);

    ptr = new QTableWidgetItem();
    ptr->setFlags(flags);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4, ptr);

    ptr = new QTableWidgetItem();
    ptr->setFlags(flags);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 6, ptr);

    //Qt::ItemFlags flags = ui->tableWidget->item(ui->tableWidget->rowCount()-1, 1)->flags() & ~Qt::ItemFlag::ItemIsEditable;

//    ui->tableWidget->item(ui->tableWidget->rowCount()-1, 1)->setFlags(flags);
//    ui->tableWidget->item(ui->tableWidget->rowCount()-1, 3)->setFlags(flags);
//    ui->tableWidget->item(ui->tableWidget->rowCount()-1, 4)->setFlags(flags);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addRow ()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);


    //продукты
    QComboBox* products = new QComboBox (ui->tableWidget);
    products->addItem("");
    products->addItems(BL.Products.values());           //добавляем значения продуктов
    products->setProperty("row", ui->tableWidget->rowCount()-1);  //указываем строку и столбец
    products->setProperty("col", 0);
    connect(products, SIGNAL(currentIndexChanged(int)),this, SLOT(productClicked(int)));
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, products);


    //единицы
    QComboBox* edin = new QComboBox (ui->tableWidget);
    edin->addItem("");
    edin->addItems(BL.Edin.values());           //добавляем значения
    edin->setProperty("row", ui->tableWidget->rowCount()-1);  //указываем строку и столбец
    edin->setProperty("col", 2);
    connect(edin, SIGNAL(currentIndexChanged(int)),this, SLOT(edinClicked(int)));
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 2, edin);




}

void MainWindow::productClicked(int pos)
{
//вбиваем код
    QTableWidgetItem* item = new QTableWidgetItem();
    Qt::ItemFlags flags = item->flags() & ~Qt::ItemFlag::ItemIsEditable;
    item->setFlags(flags);
    if (pos > 0)
    {
        item->setText( QString::number(BL.Products.key(((QComboBox*)sender())->itemText(pos))));
        ui->tableWidget->setItem(sender()->property("row").toInt(), 1, item);
        item = new QTableWidgetItem(QString::number(BL.ListPrice[pos-1], 'f', 2));
        flags = item->flags() & ~Qt::ItemFlag::ItemIsEditable;
        item->setFlags(flags);
        ui->tableWidget->setItem(sender()->property("row").toInt(), 4, item);
    }
    else
    {
        item->setText("");
        ui->tableWidget->setItem(sender()->property("row").toInt(), 1, item);
        item = new QTableWidgetItem("");
        flags = item->flags() & ~Qt::ItemFlag::ItemIsEditable;
        item->setFlags(flags);
        ui->tableWidget->setItem(sender()->property("row").toInt(), 4, item);
    }

//добавляем строку
    if (sender()->property("row") == ui->tableWidget->rowCount()-1)
        addRow ();
}

void MainWindow::edinClicked(int pos)
{
//вбиваем код
    QTableWidgetItem* item = new QTableWidgetItem();
    Qt::ItemFlags flags = item->flags() & ~Qt::ItemFlag::ItemIsEditable;
    item->setFlags(flags);
    if (pos > 0)
    {
        item->setText( QString::number(BL.Edin.key(((QComboBox*)sender())->itemText(pos))));
        ui->tableWidget->setItem(sender()->property("row").toInt(), 3, item);
    }
    else
    {
        item->setText("");
        ui->tableWidget->setItem(sender()->property("row").toInt(), 3, item);
    }
}
void MainWindow::Save ()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Сохранить форму",
                                                     QDir::currentPath(),
                                                     " (*.xlsx)");
    QXlsx::Document form ("OP16.xlsx");       //наш документ для сохранения
     //QXlsx::Document xlsx (file_name);
     //xlsx.write(form);
    form.write("A1", " Работает!");
    //xlsx.write("A1", " Работай!!");

    //xlsx.save();
    //form.save();//saveAs(file_name); //сохраняем
    form.saveAs(file_name);
}
