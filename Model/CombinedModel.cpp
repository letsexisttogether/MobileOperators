#include "CombinedModel.hpp"

CombinedModel::CombinedModel(QObject* const parent) noexcept
    : QAbstractItemModel{ parent }
{
    m_Countries =
    {
        {
            "Ukraine", "UA", 255,
            {
                { "Kyivstar", 1 },
                { "Vodafone", 2 }
            }
        },
        {
            "Poland", "PL", 260,
            {
                { "Orange", 3 },
                { "Plus", 4 }
            }
        },
        {
            "Germany", "DE", 262,
            {
                { "Telekom", 5 },
                { "O2", 6 }
            }
        },
    };
}

QModelIndex CombinedModel::index(int row, int column,
    const QModelIndex& index) const
{
    // Creates an index for PARENT element
    if (!index.isValid() && row < m_Countries.size())
    {
        return createIndex(row, column, -1);
    }

    // Creates an index for CHILD element
    if (index.internalId() == m_CountryIndex
        && row < m_Countries[index.row()].Operators.size())
    {
        return createIndex(row, column, index.row());
    }

    // Return empty (invalid) for the ROOT (internal QML) element
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
    // Return the count of countries
    if (!index.isValid())
    {
        return m_Countries.size();
    }
    // Return the count of operators in a particular Country
    else if (index.internalId() == m_CountryIndex)
    {
        return m_Countries[index.row()].Operators.size();
    }

    return {};
}

int CombinedModel::columnCount(const QModelIndex& index) const
{
    /*
    // Return the count of fields in Country
    if (!index.isValid())
    {
        return 3;
    }
    // Return the count of field in Operator
    else if (index.internalId() == m_CountryIndex)
    {
        return 2;
    }

    return {};
    */

    return 1;
}


QVariant CombinedModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
    {
        return {};
    }

    const int id = index.internalId();
    const int row = index.row();

    if (id == m_CountryIndex)
    {
        const Country& country = m_Countries[row];

        return GetCountryData(country, role);
    }

    const Country& country = m_Countries[id];
    const Operator& op = country.Operators[row];

    return GetOperatorData(op, role);
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
        :(Qt::NoItemFlags));
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

QVariant CombinedModel::GetOperatorData(const Operator& op, const int role)
    const noexcept
{
    switch (role)
    {
        case Role::OperatorName:
            return op.Name;
        case Role::Mnc:
            return op.Mnc;

        case Role::Level:
            return 1;
    }

    return {};
}
