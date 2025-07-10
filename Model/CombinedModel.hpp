#ifndef COMBINEDMODEL_HPP
#define COMBINEDMODEL_HPP

#include <QObject>
#include <QAbstractItemModel>
#include <QList>
#include <QHash>

struct Operator
{
    QString Name{};
    qint32 Mnc{};
};

struct Country
{
    QString Name{};
    QString Code{};

    qint32 Mcc{};

    QList<Operator> Operators{};
};

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
        Mcc
    };

public:
    CombinedModel(QObject* const parent = nullptr) noexcept;

    ~CombinedModel() = default;

    QModelIndex index(int row, int column, const QModelIndex& index)
        const override;
    QModelIndex parent(const QModelIndex& index) const override;

    int rowCount(const QModelIndex& index) const override;
    int columnCount(const QModelIndex& index) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QVariant GetCountryData(const Country& country, const int role)
        const noexcept;
    QVariant GetOperatorData(const Operator& op, const int role)
        const noexcept;

private:
    QList<Country> m_Countries{};

    const int m_CountryIndex{ -1 };
};

#endif // COMBINEDMODEL_HPP
