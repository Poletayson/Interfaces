#include "businesslogic.h"

BusinessLogic::BusinessLogic()
{
 //заполняем списки
    ListOrganization.append("Столовая №1");
    ListOrganization.append("Столовая №2");
    ListPodrazd.append("Склад №1");
    ListPodrazd.append("Склад №2");
    ListPodrazd.append("Холодильное помещение");

    ListPeoples.append("Иванов Иван Иванович");
    ListPeoples.append("Петров Иван Иванович");
    ListPeoples.append("Семенов Денис Игоревич");
    ListPeoples.append("Ямщиков Федор Денисович");


    Products.insert(101, "Апельсин");
    Products.insert(102, "Банан");
    Products.insert(103, "Капуста");
    Products.insert(104, "Картофель");
    Products.insert(105, "Крупа гречневая");
    Products.insert(106, "Лук");
    Products.insert(107, "Морковь");
    Products.insert(108, "Мука");
    Products.insert(109, "Пельмени");
    Products.insert(110, "Сосиски");
    Products.insert(111, "Яблоко имп.");
    Products.insert(112, "Яблоко отеч.");

    ListPrice.append(80);
    ListPrice.append(65);
    ListPrice.append(30.5);
    ListPrice.append(25);
    ListPrice.append(40.25);
    ListPrice.append(40);
    ListPrice.append(35);
    ListPrice.append(50);
    ListPrice.append(125.75);
    ListPrice.append(120);
    ListPrice.append(95);
    ListPrice.append(85.5);

    Edin.insert(166, "кг.");
    Edin.insert(168, "т.");
    Edin.insert(796, "шт.");
}
