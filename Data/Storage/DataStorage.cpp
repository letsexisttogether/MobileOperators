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
            Operator op
            {
                operatorQuery.value(0).toString(),
                operatorQuery.value(1).toInt(),
                country.Mcc
            };

            country.Operators.Insert(std::move(op));
        }

        m_Data.Insert(std::move(country));
    }
}

bool DataStorage::AddOperator(const OperatorSearchResult& searchResult,
    const QString& name, const qint32 mcc, const qint32 mnc) noexcept
{
    Operator op{ name, mnc, mcc };

    Country& country = m_Data.Unpack(m_Data.GetElementByKey(mcc));

    country.Operators.Insert(std::move(op));

    SqlManager& sqlManager = SqlManager::GetInstance();

    sqlManager.ExecuteQuery(QString{ "INSERT INTO operators "
        "VALUES (%1, %2, '%3')"}
        .arg(op.Mcc)
        .arg(op.Mnc)
        .arg(op.Name));

    return true;
}

bool DataStorage::UpdateOperator(const OperatorSearchResult& searchResult,
    const QString& name) noexcept
{
    /*
    auto& op = m_Countries[searchResult.CountryIndex]
        .Operators[searchResult.OperatorIndex];

    op.Name = name;

    SqlManager& sqlManager = SqlManager::GetInstance();

    sqlManager.ExecuteQuery(QString{ "UPDATE operators "
        "SET name = '%1' "
        "WHERE mcc = %2 AND mnc = %3" }
        .arg(op.Name)
        .arg(op.Mcc)
        .arg(op.Mnc));

*/
    return true;
}

bool DataStorage::RemoveOperator(const OperatorSearchResult& searchResult)
    noexcept
{
    /*
    auto& country = m_Countries[searchResult.CountryIndex];
    const auto& op = country.Operators[searchResult.OperatorIndex];

    SqlManager& sqlManager = SqlManager::GetInstance();

    sqlManager.ExecuteQuery(QString{ "DELETE FROM operators "
        "WHERE mcc = %1 AND mnc = %2" }
        .arg(op.Mcc)
        .arg(op.Mnc));

    country.Operators.removeAt(searchResult.OperatorIndex);
*/
    return true;
}

const DataStorage::DataStructure& DataStorage::GetData() const noexcept
{
    return m_Data;
}

DataStorage::OperatorSearchResult DataStorage::FindOperator
    (const qint32 mcc, const qint32 mnc) const noexcept
{
    if (!m_Data.DoesContainKey(mcc))
    {
        return {};
    }

    const auto& operators = m_Data.Unpack(m_Data.GetElementByKey(mcc))
        .Operators;

    if (!operators.DoesContainKey(mnc))
    {
        return {};
    }

    return { m_Data.GetIndex(mcc), operators.GetIndex(mnc), true };
}


DataStorage::OperatorSearchResult DataStorage::FindCountry
    (const qint32 mcc) const noexcept
{
    if (!m_Data.DoesContainKey(mcc))
    {
        return {};
    }

    return { m_Data.GetIndex(mcc), 0, true };
}
