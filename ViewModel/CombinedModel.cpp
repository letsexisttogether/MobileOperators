#include "CombinedModel.hpp"

#include <QStringLiteral>

CombinedModel::CombinedModel(QObject* const parent) noexcept
    : QAbstractItemModel{ parent }
{}

QModelIndex CombinedModel::index(int row, int column,
    const QModelIndex& index) const
{
    const auto& countries = m_Storage.GetData();

    if (!index.isValid() && countries.DoesContainIndex(row))
    {
        return createIndex(row, column, -1);
    }

    if (index.internalId() == m_CountryIndex
        && countries.Unpack(countries.GetElementByIndex(index.row()))
            .Operators.DoesContainIndex(row))
    {
        return createIndex(row, column, index.row());
    }

    return {};
}

QModelIndex CombinedModel::parent(const QModelIndex& index) const
{
    if (!index.isValid() || index.internalId() == m_CountryIndex)
    {
        return {};
    }

    return createIndex(index.internalId(), 0, -1);
}

int CombinedModel::rowCount(const QModelIndex& index) const
{
    const auto& countries = m_Storage.GetData();

    if (!index.isValid())
    {
        return countries.Size();
    }
    else if (const int row = index.row();
        index.internalId() == m_CountryIndex
        && countries.DoesContainIndex(row))
    {
        const auto& country = countries.Unpack(countries
            .GetElementByIndex(row));

        return country.Operators.Size();
    }

    return {};
}

int CombinedModel::columnCount(const QModelIndex& index) const
{
    return 1;
}

QVariant CombinedModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
    {
        return {};
    }

    const auto& countries = m_Storage.GetData();

    const int id = index.internalId();
    const int row = index.row();

    if (id == m_CountryIndex)
    {
        if (countries.DoesContainIndex(row))
        {
            const Country& country = countries.Unpack(
                countries.GetElementByIndex(row));

            return GetCountryData(country, role);
        }
        else
        {
            qDebug() << "[Error] The index for country " << row
                << " is invalid";

            return {};
        }
    }

    if (countries.DoesContainIndex(id))
    {
        const Country& country = countries.Unpack(countries
            .GetElementByIndex(id));

        const auto& operators = country.Operators;

        if (operators.DoesContainIndex(row))
        {
            const Operator& op = operators.Unpack(operators
                .GetElementByIndex(row));

            return GetOperatorData(country, op, role);
        }
        else
        {
            qDebug() << "[Error] The index for country: " << id
                << " is invalid";

            return {};
        }
    }

    qDebug() << "[Error] The index for country: " << id
        << " is invalid";

    return {};
}

QHash<int, QByteArray> CombinedModel::roleNames() const
{
    return
    {
        { Role::OperatorName, "operatorName" },
        { Role::Mnc, "mnc" },

        { Role::CountryName, "countryName" },
        { Role::CountryCode, "countryCode" },
        { Role::Mcc, "mcc" },

        { Role::Level, "level" }
    };
}

Qt::ItemFlags CombinedModel::flags(const QModelIndex& index) const
{
    return ((index.isValid()) ? (Qt::ItemIsEnabled | Qt::ItemIsSelectable)
        : (Qt::NoItemFlags));
}

void CombinedModel::AddOperator(const QString& name, const qint32 mcc,
    const qint32 mnc) noexcept
{
    /*
    const auto searchResult = m_Storage.FindCountry(mcc);

    if (!searchResult.Result)
    {
        return;
    }

    const qsizetype operatorsCount = m_Storage.GetData()
        [searchResult.CountryIndex].Operators.size();

    QModelIndex parent{ index(searchResult.CountryIndex, 0) };

    beginInsertRows(parent, operatorsCount, operatorsCount);

    if (!m_Storage.AddOperator(searchResult, name, mcc, mnc))
    {

    }
    else
    {
        endInsertRows();
    }
    */
}

void CombinedModel::UpdateOperator(const QString& name, const qint32 mcc,
    const qint32 mnc) noexcept
{
    /*
    const auto searchResult = m_Storage.FindOperator(mcc, mnc);

    if (!searchResult.Result)
    {
        return;
    }

    if (!m_Storage.UpdateOperator(searchResult, name))
    {
        return;
    }

    const QModelIndex changedIndex
    {
        index(searchResult.OperatorIndex, 0,
            index(searchResult.CountryIndex, 0))
    };

    emit dataChanged(changedIndex, changedIndex, { Role::OperatorName });
    */
}

void CombinedModel::RemoveOperator(const qint32 mcc, const qint32 mnc) noexcept
{
    /*
    const auto searchResult = m_Storage.FindOperator(mcc, mnc);

    if (!searchResult.Result)
    {
        return;
    }

    beginRemoveRows(index(searchResult.CountryIndex, 0),
        searchResult.OperatorIndex, searchResult.OperatorIndex);

    if (!m_Storage.RemoveOperator(searchResult))
    {
        beginResetModel();
        endResetModel();
    }
    else
    {
        endRemoveRows();
    }
    */
}

QVariant CombinedModel::GetCountryData(const Country& country, const int role)
    const noexcept
{
    switch (role)
    {
        case Role::CountryName:
            return country.Name;
        case Role::CountryCode:
            return country.Code;
        case Role::Mcc:
            return country.Mcc;
        case Role::Level:
            return 0;
    }

    return {};
}

QVariant CombinedModel::GetOperatorData(const Country& country,
    const Operator& op, const int role) const noexcept
{
    if (auto variant = GetCountryData(country, role);
        role != Role::Level && !variant.isNull())
    {
        return variant;
    }

    switch (role)
    {
        case Role::OperatorName:
            return op.Name;
        case Role::Mnc:
            return op.Mnc;
        case Role::Mcc:
            return op.Mcc;
        case Role::Level:
            return 1;
    }

    return {};
}
