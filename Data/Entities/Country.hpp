#ifndef COUNTRY_HPP
#define COUNTRY_HPP

#include <QList>

#include "Data/Structures/IndexedMap.hpp"
#include "Operator.hpp"

struct Country
{
    QString Name{};
    QString Code{};

    qint32 Mcc{};

    IndexedMap<Operator, qint32, &Operator::Mnc> Operators{};

};

#endif
