#ifndef COMBINEDMODEL_HPP
#define COMBINEDMODEL_HPP

#include <QObject>
#include <QAbstractItemModel>
#include <QList>
#include <QHash>

#include "Data/Storage/DataStorage.hpp"

class CombinedModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Role
    {
        OperatorName = Qt::UserRole + 1,
        Mnc,

        CountryName,
        CountryCode,
        Mcc,

        Level
    };

private:
    struct OperatorSearchResult
    {
        qsizetype CountryIndex{};
        qsizetype OperatorIndex{};
        bool Result{};
    };

public:
    CombinedModel(QObject* const parent = nullptr) noexcept;

    ~CombinedModel() = default;

    QModelIndex index(int row, int column, const QModelIndex& index = {})
        const override;
    QModelIndex parent(const QModelIndex& index) const override;

    int rowCount(const QModelIndex& index) const override;
    int columnCount(const QModelIndex& index) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

public slots:
    /*
    void UpdateOperator(const QString& name, const qint32 mcc,
        const qint32 mnc) noexcept;
    */

    void AddOperator(const qint32 mcc, const qint32 mnc,
        const QString& name) noexcept;
    void RemoveOperator(const qint32 mcc, const qint32 mnc) noexcept;

private:
    QVariant GetCountryData(const Country& country, const int role)
        const noexcept;
    QVariant GetOperatorData(const Operator& op, const int role)
        const noexcept;

private:
    DataStorage m_Storage{ this };

    const int m_CountryIndex{ -1 };
};

#endif
