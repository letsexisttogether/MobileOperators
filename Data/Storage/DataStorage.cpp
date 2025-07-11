#include "DataStorage.hpp"

#include <SQL/SqlManager.hpp>

DataStorage::DataStorage(QObject* const parent)
    : QObject{ parent }
{
    SqlManager& sqlManager = SqlManager::GetInstance();

    QSqlQuery countryQuery
    {
        sqlManager.ExecuteQuery("SELECT name, code, "
            "mcc FROM countries")
    };

    while (countryQuery.next())
    {
        Country country
        {
            countryQuery.value(0).toString(),
            countryQuery.value(1).toString(),
            countryQuery.value(2).toInt()
        };

        const QString queryText
        {
            QString
            {
                "SELECT name, mnc FROM operators "
                "WHERE mcc = %1"
            }
            .arg(country.Mcc)
        };

        QSqlQuery operatorQuery
        {
            sqlManager.ExecuteQuery(queryText)
        };

        while (operatorQuery.next())
        {
            const Operator op
            {
                operatorQuery.value(0).toString(),
                operatorQuery.value(1).toInt(),
                country.Mcc
            };

            country.Operators.append(op);
        }

        m_Countries.append(country);
    }
}

// TODO: Finish the method
DataStorage::OperatorSearchResult DataStorage::AddOperator
    (const qint32 mcc, const qint32 mnc) noexcept
{
    const OperatorSearchResult searchResult
    {
        FindOperator(mcc, mnc)
    };

    if (searchResult.Result)
    {
        qDebug() << "[Warning] Such an operator already exists";
    }

    return searchResult;
}

bool DataStorage::RemoveOperator(const OperatorSearchResult& searchResult)
    noexcept
{
    if (!searchResult.Result)
    {
        qDebug() << "[Warning] There's no such operator";
    }

    auto& country = m_Countries[searchResult.CountryIndex];
    const auto& op = country.Operators[searchResult.OperatorIndex];

    SqlManager& sqlManager = SqlManager::GetInstance();

    sqlManager.ExecuteQuery(QString{ "DELETE FROM operators "
        "WHERE mcc = %1 AND mnc = %2" }
        .arg(op.Mcc)
        .arg(op.Mnc));

    country.Operators.removeAt(searchResult.OperatorIndex);

    return true;
}

const QList<Country>& DataStorage::GetData() const noexcept
{
    return m_Countries;
}

DataStorage::OperatorSearchResult DataStorage::FindOperator
    (const qint32 mcc, const qint32 mnc) const noexcept
{
    for (qsizetype i = 0; i < m_Countries.size(); ++i)
    {
        const Country& country = m_Countries[i];

        if (country.Mcc != mcc)
        {
            continue;
        }

        const auto& operators = country.Operators;

        for (qsizetype j = 0; j < operators.size(); ++j)
        {
            if (operators[j].Mnc == mnc)
            {
                return { i, j, true };
            }
        }
    }

    return {};
}
