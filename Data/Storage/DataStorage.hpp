#ifndef DATASTORAGE_HPP
#define DATASTORAGE_HPP

#include <QObject>

#include "Data/Entities/Country.hpp"

class DataStorage : public QObject
{
    Q_OBJECT

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

    OperatorSearchResult AddOperator(const qint32 mcc, const qint32 mnc) noexcept;
    bool RemoveOperator(const OperatorSearchResult& searchResult) noexcept;

    OperatorSearchResult FindOperator(const qint32 mcc, const qint32 mnc)
        const noexcept;

    const QList<Country>& GetData() const noexcept;

signals:
    void DatabaseError();

private:
    QList<Country> m_Countries{};
};

#endif // DATASTORAGE_HPP
