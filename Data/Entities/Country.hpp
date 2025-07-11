#ifndef COUNTRY_HPP
#define COUNTRY_HPP

#include <QList>

#include "Operator.hpp"

struct Country
{
    QString Name{};
    QString Code{};

    qint32 Mcc{};

    QList<Operator> Operators{};
};

#endif
