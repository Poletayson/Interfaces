#ifndef BUSINESSLOGIC_H
#define BUSINESSLOGIC_H

#include <QList>
#include <QMap>

class BusinessLogic
{
public:
    QList<QString> ListOrganization;
    QList<QString> ListPodrazd;
    QList<QString> ListPeoples;
    QMap <int, QString> Products;
    QList<float> ListPrice;
    QMap <int, QString> Edin;

    BusinessLogic();
};

#endif // BUSINESSLOGIC_H
