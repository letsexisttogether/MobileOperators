#ifndef SQLMANAGER_HPP
#define SQLMANAGER_HPP

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QScopedPointer>

class SqlManager
{
public:
    static void Init(const QString& driver, const QString& dbName) noexcept;
    static SqlManager& GetInstance(const bool initIfAbsent = true) noexcept;

public:
    SqlManager() = delete;
    ~SqlManager() = default;

    QSqlQuery ExecuteQuery(const QString& query) noexcept;

    bool CheckConnection() const noexcept;

private:
    SqlManager(const QString& driver, const QString& dbName) noexcept;

private:
    inline static QScopedPointer<SqlManager> m_Instance{};

private:
    QSqlDatabase m_DB;
};

#endif
