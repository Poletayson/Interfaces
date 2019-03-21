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


    for (int i = 1; i <=5; i++)     //добавляем по строке
        addRow (i);



    ui->comboBoxOrganization->addItem("");
    ui->comboBoxOrganization->addItems(BL.Organization.values());           //добавляем организации
    ui->comboBoxPodrazd->addItem("");
    ui->comboBoxPodrazd->addItems(BL.Podrazdel.values());           //добавляем подразделения

    ui->comboBoxMatL->addItem("");                          //отв. лицо
    ui->comboBoxMatL->addItems(BL.ListPeoples);
    ui->comboBoxMatD->addItem("");                          //должность
    ui->comboBoxMatD->addItems(BL.ListDolznost);
    ui->comboBoxProvL->addItem("");
    ui->comboBoxProvL->addItems(BL.ListPeoples);
    ui->comboBoxProvD->addItem("");                         //пров.
    ui->comboBoxProvD->addItems(BL.ListDolznost);           //должность


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addRow (int n)
{
    QTableWidget* tWidget;
    switch (n)          //выбираем куда добавим
    {
    case 1:
    {
        tWidget = ui->tableWidget;
        break;
    }
    case 2:
    {
        tWidget = ui->tableWidget_2;
        break;
    }
    case 3:
    {
        tWidget = ui->tableWidget_3;
        break;
    }
    case 4:
    {
        tWidget = ui->tableWidget_4;
        break;
    }
    case 5:
    {
        tWidget = ui->tableWidget_5;
        break;
    }
    default:
        break;
    }



    tWidget->setRowCount(tWidget->rowCount() + 1);
    //устанавливаем запрет на редактирование
    QTableWidgetItem* ptr = new QTableWidgetItem();
    Qt::ItemFlags flags = ptr->flags() & ~Qt::ItemFlag::ItemIsEditable;
    ptr->setFlags(flags);


    //продукты
    if (n == 1) //комбобокс
    {
        QComboBox* products = new QComboBox (tWidget);
        products->addItem("");
        products->addItems(BL.Products.values());           //добавляем значения продуктов
        products->setProperty("row", tWidget->rowCount()-1);  //указываем строку и столбец
        products->setProperty("col", 0);
        connect(products, SIGNAL(currentIndexChanged(int)),this, SLOT(productClicked(int)));
        tWidget->setCellWidget(tWidget->rowCount()-1, 0, products);
    }
    else
    {
        tWidget->setItem(tWidget->rowCount()-1, 0, ptr);    //просто поле
        ptr = new QTableWidgetItem();
        ptr->setFlags(flags);
    }


    //единицы
    if(n == 1)
    {
        QComboBox* edin = new QComboBox (tWidget);
        edin->addItem("");
        edin->addItems(BL.Edin.values());           //добавляем значения
        edin->setProperty("row", tWidget->rowCount()-1);  //указываем строку и столбец
        connect(edin, SIGNAL(currentIndexChanged(int)),this, SLOT(edinClicked(int)));
        edin->setProperty("col", 2);
        tWidget->setCellWidget(tWidget->rowCount()-1, 2, edin);
    }
    else
    {
        tWidget->setItem(tWidget->rowCount()-1, 1, ptr);    //просто поле
        ptr = new QTableWidgetItem();
        ptr->setFlags(flags);
    }


    if (n == 1)     //только в первую таблицу помещаем коды
    {
    //ptr->setFlags(flags);
        tWidget->setItem(tWidget->rowCount()-1, 1, ptr);

        ptr = new QTableWidgetItem();
        ptr->setFlags(flags);
        tWidget->setItem(tWidget->rowCount()-1, 3, ptr);
        ptr = new QTableWidgetItem();
        ptr->setFlags(flags);
    }


    if (n == 1)
        tWidget->setItem(tWidget->rowCount()-1, 4, ptr);
    else
        tWidget->setItem(tWidget->rowCount()-1, 2, ptr);


    ptr = new QTableWidgetItem();
    ptr->setFlags(flags);
    if (n == 1)
        tWidget->setItem(tWidget->rowCount()-1, 6, ptr);
    else
        tWidget->setItem(tWidget->rowCount()-1, 4, ptr);


    ptr = new QTableWidgetItem();
    if (n == 1)
        tWidget->setItem(tWidget->rowCount()-1, 5, ptr);
    else
        tWidget->setItem(tWidget->rowCount()-1, 3, ptr);
}

void MainWindow::productClicked(int pos)
{
//вбиваем код
    QTableWidgetItem* item = new QTableWidgetItem();
    QTableWidgetItem* itemOther = new QTableWidgetItem();   //для других таблиц
    Qt::ItemFlags flags = item->flags() & ~Qt::ItemFlag::ItemIsEditable;
    item->setFlags(flags);
    if (pos > 0)
    {
        item->setText( QString::number(BL.Products.key(((QComboBox*)sender())->itemText(pos))));//или ->currentText()
        ui->tableWidget->setItem(sender()->property("row").toInt(), 1, item);
        item = new QTableWidgetItem(QString::number(BL.ListPrice[pos-1], 'f', 2));
        flags = item->flags() & ~Qt::ItemFlag::ItemIsEditable;
        item->setFlags(flags);
        ui->tableWidget->setItem(sender()->property("row").toInt(), 4, item);

        ///в остальные - только название продукта
        itemOther = new QTableWidgetItem(((QComboBox*)sender())->currentText());
        item->setFlags(flags);
        ui->tableWidget_2->setItem(sender()->property("row").toInt(), 0, itemOther);
        itemOther = new QTableWidgetItem(((QComboBox*)sender())->currentText());
        item->setFlags(flags);
        ui->tableWidget_3->setItem(sender()->property("row").toInt(), 0, itemOther);
        itemOther = new QTableWidgetItem(((QComboBox*)sender())->currentText());
        item->setFlags(flags);
        ui->tableWidget_4->setItem(sender()->property("row").toInt(), 0, itemOther);
        itemOther = new QTableWidgetItem(((QComboBox*)sender())->currentText());
        item->setFlags(flags);
        ui->tableWidget_5->setItem(sender()->property("row").toInt(), 0, itemOther);

        ///цены
        itemOther = new QTableWidgetItem(QString::number(BL.ListPrice[pos-1], 'f', 2));
        itemOther->setFlags(flags);
        ui->tableWidget_2->setItem(sender()->property("row").toInt(), 2, itemOther);
        itemOther = new QTableWidgetItem(QString::number(BL.ListPrice[pos-1], 'f', 2));
        itemOther->setFlags(flags);
        ui->tableWidget_3->setItem(sender()->property("row").toInt(), 2, itemOther);
        itemOther = new QTableWidgetItem(QString::number(BL.ListPrice[pos-1], 'f', 2));
        itemOther->setFlags(flags);
        ui->tableWidget_4->setItem(sender()->property("row").toInt(), 2, itemOther);
        itemOther = new QTableWidgetItem(QString::number(BL.ListPrice[pos-1], 'f', 2));
        itemOther->setFlags(flags);
        ui->tableWidget_5->setItem(sender()->property("row").toInt(), 2, itemOther);

    }
    else
    {
        item->setText("");
        ui->tableWidget->setItem(sender()->property("row").toInt(), 1, item);
        item = new QTableWidgetItem("");
        flags = item->flags() & ~Qt::ItemFlag::ItemIsEditable;
        item->setFlags(flags);
        ui->tableWidget->setItem(sender()->property("row").toInt(), 4, item);

        ///в остальные - только название продукта
        itemOther = new QTableWidgetItem("");
        itemOther->setFlags(flags);
        ui->tableWidget_2->setItem(sender()->property("row").toInt(), 0, itemOther);
        itemOther = new QTableWidgetItem("");
        itemOther->setFlags(flags);
        ui->tableWidget_3->setItem(sender()->property("row").toInt(), 0, itemOther);
        itemOther = new QTableWidgetItem("");
        itemOther->setFlags(flags);
        ui->tableWidget_4->setItem(sender()->property("row").toInt(), 0, itemOther);
        itemOther = new QTableWidgetItem("");
        itemOther->setFlags(flags);
        ui->tableWidget_5->setItem(sender()->property("row").toInt(), 0, itemOther);

        ///цены
        itemOther = new QTableWidgetItem("");
        itemOther->setFlags(flags);
        ui->tableWidget_2->setItem(sender()->property("row").toInt(), 2, itemOther);
        itemOther = new QTableWidgetItem("");
        itemOther->setFlags(flags);
        ui->tableWidget_3->setItem(sender()->property("row").toInt(), 2, itemOther);
        itemOther = new QTableWidgetItem("");
        itemOther->setFlags(flags);
        ui->tableWidget_4->setItem(sender()->property("row").toInt(), 2, itemOther);
        itemOther = new QTableWidgetItem("");
        itemOther->setFlags(flags);
        ui->tableWidget_5->setItem(sender()->property("row").toInt(), 2, itemOther);
    }

//добавляем строку
    if (sender()->property("row") == ui->tableWidget->rowCount()-1)
        for (int i = 1; i <=5; i++)      //добавляем по строке
            addRow (i);
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

void MainWindow::on_tableWidget_cellChanged(int row, int column)    //клик по ячейке
{
    if (column == 5)
    {
        bool* ok = new bool;
        ui->tableWidget->item(row, column)->text().toFloat(ok);
        if(ok)              //имеем число
        {
            ui->tableWidget->item(row, 6)->setText(QString::number(ui->tableWidget->item(row, 5)->text().toFloat() * ui->tableWidget->item(row, 4)->text().toFloat(), 'f', 2)); //устанавливаем сумму
        }
    }
}

void MainWindow::Save ()    //сохраняем в файл
{
    QString file_name = QFileDialog::getSaveFileName(this, "Сохранить форму",
                                                     QDir::currentPath(),
                                                     " (*.xlsx)");
    QXlsx::Document form ("OP16.xlsx");       //наш документ для сохранения

    if (ui->lineEditNumDoc->text().length() > 0)        //номер документа
        form.write("AO14", ui->lineEditNumDoc->text());
    form.write("AX14", ui->dateEditDoc->text());        //дата
    form.write("AF20", ui->dateEditDoc->date().day());        //дата остатка
    form.write("AF39", ui->dateEditDoc->date().day());        //дата остатка
    form.write("AH20", ui->dateEditDoc->date().month());        //дата остатка
    form.write("AH39", ui->dateEditDoc->date().month());        //дата остатка
    form.write("AL20", ui->dateEditDoc->date().year()%1000);        //дата остатка
    form.write("AL39", ui->dateEditDoc->date().year()%1000);        //дата остатка

    if (ui->comboBoxOrganization->currentIndex()>0)     //индекс организации больше 0 (не пустая)
    {
        form.write("A6", ui->comboBoxOrganization->currentText());        //организация
        form.write("BU6", BL.Organization.key(ui->comboBoxOrganization->currentText())); //код по ОКПО
    }
    if (ui->comboBoxPodrazd->currentIndex()>0)     //индекс подразделения больше 0 (не пустая)
    {
        form.write("A8", ui->comboBoxPodrazd->currentText());        //организация
        form.write("BU7", BL.Podrazdel.key(ui->comboBoxPodrazd->currentText())); //код по ОКПО
    }
    if (ui->comboBoxMatL->currentIndex()>0)     //есть отв лицо
    {
        form.write("AH16", ui->comboBoxMatL->currentText());        //отв. лицо
    }
    if (ui->comboBoxMatD->currentIndex()>0)     //индекс должности больше 0 (не пусто)
    {
        form.write("S16", ui->comboBoxMatD->currentText());        //отв. лицо
    }
    if (ui->comboBoxProvL->currentIndex()>0)     //индекс подразделения больше 0 (не пустая)
    {
        form.write("BE69", ui->comboBoxProvL->currentText());        //отв. лицо
    }
    if (ui->comboBoxProvD->currentIndex()>0)     //индекс подразделения больше 0 (не пустая)
    {
        form.write("AI69", ui->comboBoxProvD->currentText());        //отв. лицо
    }

    float sum = 0;
    for (int i = 0; i < (ui->tableWidget->rowCount() - 1) && i <= 9; i++)   //все строки таблицы кроме пустой
    {
        if (((QComboBox*)ui->tableWidget->cellWidget(i, 0))->currentText().length() > 0)    //поле продукта непустое
        {
            form.write("A" + QString::number(25 + i), QString::number(i + 1));        //номер записи
            form.write("D" + QString::number(25 + i), ((QComboBox*)ui->tableWidget->cellWidget(i, 0))->currentText());        //текущий продукт
            form.write("P" + QString::number(25 + i), ui->tableWidget->item(i, 1)->text());        //код продукта
            form.write("T" + QString::number(25 + i), ((QComboBox*)ui->tableWidget->cellWidget(i, 2))->currentText());        //единица изм.
            form.write("X" + QString::number(25 + i), ui->tableWidget->item(i, 3)->text());        //код единицы
            form.write("AA" + QString::number(25 + i), ui->tableWidget->item(i, 4)->text());        //код единицы
            form.write("AE" + QString::number(25 + i), ui->tableWidget->item(i, 5)->text());        //код единицы
            form.write("AI" + QString::number(25 + i), ui->tableWidget->item(i, 6)->text());        //код единицы
            sum += ui->tableWidget->item(i, 6)->text().toFloat();
        }
    }
    form.write("AI35", QString::number(sum, 'f', 2));

//заполняем оборотную сторону формы
    float sum2 = 0;
    for (int i = 0; i + 10 < (ui->tableWidget->rowCount() - 1) && i <= 21; i++)   //все строки таблицы кроме пустой
    {
        int j = i + 10;
        if (((QComboBox*)ui->tableWidget->cellWidget(j, 0))->currentText().length() > 0)    //поле продукта непустое
        {
            form.write("A" + QString::number(44 + i), QString::number(j + 1));        //номер записи
            form.write("D" + QString::number(44 + i), ((QComboBox*)ui->tableWidget->cellWidget(j, 0))->currentText());        //текущий продукт
            form.write("P" + QString::number(44 + i), ui->tableWidget->item(j, 1)->text());        //код продукта
            form.write("T" + QString::number(44 + i), ((QComboBox*)ui->tableWidget->cellWidget(j, 2))->currentText());        //единица изм.
            form.write("X" + QString::number(44 + i), ui->tableWidget->item(j, 3)->text());        //код единицы
            form.write("AA" + QString::number(44 + i), ui->tableWidget->item(j, 4)->text());        //код единицы
            form.write("AE" + QString::number(44 + i), ui->tableWidget->item(j, 5)->text());        //код единицы
            form.write("AI" + QString::number(44 + i), ui->tableWidget->item(j, 6)->text());        //код единицы
            sum2 += ui->tableWidget->item(j, 6)->text().toFloat();
        }
    }
    form.write("AI66", QString::number(sum2, 'f', 2));
    form.write("AI67", QString::number(sum2 + sum, 'f', 2));


    //xlsx.save();
    //form.save();//saveAs(file_name); //сохраняем
    form.saveAs(file_name);
}


///изменилась вкладка
void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index != 0)
    {
//        QLayout* ptr = ui->tabWidget->currentWidget();//ui->tabWidget->layout();
//        (ui->tabWidget->layout())->addWidget(ui->tableWidget);
        //((QGridLayout*)ui->tabWidget->currentWidget())->removeWidget(ui->tableWidget);
        //if ()
    }
    else
    {

    }
}
