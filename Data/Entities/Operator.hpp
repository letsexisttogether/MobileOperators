#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <QString>
#include <QtTypes>
#include <QHash>

struct Operator
{
    QString Name{};
    qint32 Mnc{};
    qint32 Mcc{};
};

#endif
