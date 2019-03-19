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
    if (pos > 0)
    {
        item->setText( QString::number(BL.Products.key(((QComboBox*)sender())->itemText(pos))));
        ui->tableWidget->setItem(sender()->property("row").toInt(), 1, item);
        item = new QTableWidgetItem(QString::number(BL.ListPrice[pos-1], 'f', 2));
        ui->tableWidget->setItem(sender()->property("row").toInt(), 4, item);
    }
    else
    {
        item->setText("");
        ui->tableWidget->setItem(sender()->property("row").toInt(), 1, item);
        item = new QTableWidgetItem("");
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
                                                     " (*.xls)");


    //file_name += ".jpg";
//    QPixmap pix_map = QPixmap::grabWidget(ui->widget);
//    QPixmap pix_map2 = pix_map.copy(1, 1, 678, 258);
//    if (!pix_map2.save(file_name)) {
//        QMessageBox::information(this, "Предупреждение",
//                                 "Картинка не была сохранена");
//    }
//    addRow();
}
