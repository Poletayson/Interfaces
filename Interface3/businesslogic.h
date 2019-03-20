#ifndef BUSINESSLOGIC_H
#define BUSINESSLOGIC_H

#include <QList>
#include <QMap>

class BusinessLogic
{
public:
    QList<QString> ListPeoples;
    QList<QString> ListDolznost;
    QMap <int, QString> Products;
    QMap <int, QString> Organization;
    QMap <int, QString> Podrazdel;
    QList<float> ListPrice;
    QMap <int, QString> Edin;

    BusinessLogic();
};

#endif // BUSINESSLOGIC_H
