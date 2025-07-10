#include "SqlManager.hpp"

#include <QDebug>
#include <QSqlError>
#include <QStringLiteral>

void SqlManager::Init(const QString& driver, const QString& dbName) noexcept
{
    if (m_Instance)
    {
        qDebug() << "[Error] An attempt of initializing a complete object";

        return;
    }

    m_Instance.reset(new SqlManager{ driver, dbName });
}

SqlManager& SqlManager::GetInstance(const bool initIfAbsent) noexcept
{
    if (!m_Instance)
    {
        qDebug() << "[Error] Attempt to get an uninitialized instance";

        // Prevents the memory violation
        if (initIfAbsent)
        {
            Init("", "");
        }
    }

    return *m_Instance;
}

SqlManager::SqlManager(const QString& driver, const QString& dbName) noexcept
    : m_DB{ QSqlDatabase::addDatabase(driver) }
{
    m_DB.setDatabaseName(dbName);
    m_DB.open();

    CheckConnection();
}

// TODO: make custon QSqlQuery
QSqlQuery SqlManager::ExecuteQuery(const QString& query) noexcept
{
    QSqlQuery sqlQuery{ m_DB };

    if (!sqlQuery.exec(query))
    {
        qDebug() << "[Error] Query was not executed: "
            << sqlQuery.lastError();

    }

    // Not the best practice
    return sqlQuery;
}

bool SqlManager::CheckConnection() const noexcept
{
    const QString connectionInformation
    {
        QStringLiteral("The connection to [%1]")
            .arg(m_DB.databaseName())
    };

    if (m_DB.isOpen())
    {
        qDebug() << connectionInformation << "is OPEN";

        return true;
    }

    qDebug() << "[Error] " << connectionInformation << "is CLOSED"
             << "The last error is" << m_DB.lastError();

    return false;
}
