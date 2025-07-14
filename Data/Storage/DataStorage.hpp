#ifndef DATASTORAGE_HPP
#define DATASTORAGE_HPP

#include <QObject>

#include "Data/Entities/Country.hpp"
#include "Data/Structures/IndexedMap.hpp"

class DataStorage : public QObject
{
    Q_OBJECT

public:
    using DataStructure = IndexedMap<Country, qint32, &Country::Mcc>;

public:
    struct OperatorSearchResult
    {
        qsizetype CountryIndex{};
        qsizetype OperatorIndex{};
        bool Result{};
    };

public:
    explicit DataStorage(QObject* const parent = nullptr);
    ~DataStorage() = default;

    bool AddOperator(const OperatorSearchResult& searchResult,
        const QString& name, const qint32 mcc, const qint32 mnc) noexcept;
    bool RemoveOperator(const OperatorSearchResult& searchResult) noexcept;
    bool UpdateOperator(const OperatorSearchResult& searchResult,
        const QString& name) noexcept;

    OperatorSearchResult FindOperator(const qint32 mcc, const qint32 mnc)
        const noexcept;
    OperatorSearchResult FindCountry(const qint32 mcc) const noexcept;

    const DataStructure& GetData() const noexcept;

private:
    DataStructure m_Data{};
};

#endif
