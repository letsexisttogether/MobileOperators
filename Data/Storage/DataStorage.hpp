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

    bool AddOperator(Operator&& op) noexcept;
    bool RemoveOperator(const Operator& op) noexcept;
    bool UpdateOperator(const Operator& op) noexcept;

    const DataStructure& GetData() const noexcept;

private:
    DataStructure m_Data{};
};

#endif
