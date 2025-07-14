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

bool DataStorage::AddOperator(Operator&& op) noexcept
{
    const qint32 mcc = op.Mcc;

    if (!m_Data.DoesContainKey(mcc))
    {
        qDebug() << "[Error] Provided MCC " << mcc
            << " does not belong to any country";

        return false;
    }

    SqlManager& sqlManager = SqlManager::GetInstance();

    sqlManager.ExecuteQuery(QString{ "INSERT INTO operators "
        "VALUES (%1, %2, '%3')"}
        .arg(op.Mcc)
        .arg(op.Mnc)
        .arg(op.Name));

    auto& country = m_Data.Unpack(m_Data.GetElementByKey(mcc));

    return country.Operators.Insert(std::move(op));
}

bool DataStorage::RemoveOperator(const Operator& op) noexcept
{
    const qint32 mcc = op.Mcc;

    if (!m_Data.DoesContainKey(mcc))
    {
        qDebug() << "[Error] Provided MCC " << mcc
            << " does not belong to any country";

        return false;
    }

    auto& country = m_Data.Unpack(m_Data.GetElementByKey(mcc));
    auto& operators = country.Operators;

    const qint32 mnc = op.Mnc;

    if (!operators.DoesContainKey(mnc))
    {
        qDebug() << "[Error] Provided MNC " << mnc
            << " does not belong to any operator";

        return false;
    }

    SqlManager& sqlManager = SqlManager::GetInstance();

    sqlManager.ExecuteQuery(QString{ "DELETE FROM operators "
        "WHERE mcc = %1 AND mnc = %2" }
        .arg(op.Mcc)
        .arg(op.Mnc));

    return operators.Remove(mnc);;
}

bool DataStorage::UpdateOperator(const Operator& op) noexcept
{
    const qint32 mcc = op.Mcc;

    if (!m_Data.DoesContainKey(mcc))
    {
        qDebug() << "[Error] Provided MCC " << mcc
            << " does not belong to any country";

        return false;
    }

    auto& country = m_Data.Unpack(m_Data.GetElementByKey(mcc));
    auto& operators = country.Operators;

    const qint32 mnc = op.Mnc;

    if (!operators.DoesContainKey(mnc))
    {
        qDebug() << "[Error] Provided MNC " << mnc
            << " does not belong to any operator";

        return false;
    }

    operators.Unpack(operators.GetElementByKey(mnc)) = op;

    SqlManager& sqlManager = SqlManager::GetInstance();

    sqlManager.ExecuteQuery(QString{
            "UPDATE operators "
            "SET name = '%1' "
            "WHERE mcc = %2 AND mnc = %3" }
        .arg(op.Name)
        .arg(op.Mcc)
        .arg(op.Mnc));

    return true;
}

const DataStorage::DataStructure& DataStorage::GetData() const noexcept
{
    return m_Data;
}
