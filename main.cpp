#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "SQL/SqlManager.hpp"
#include "ViewModel/CombinedModel.hpp"

int main(int argc, char* argv[])
{
    QGuiApplication app{ argc, argv };

    const QString resourcesPath
    {
        QGuiApplication::applicationDirPath()
            + "/Resources/"
    };

    SqlManager::Init("QSQLITE", resourcesPath
        + "Database/OM system.db");

    QQmlApplicationEngine engine{};

    CombinedModel model{};
    engine.rootContext()->setContextProperty("combinedModel",
        &model);

    engine.rootContext()->setContextProperty("resourcesPath",
        resourcesPath);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("MobileOperators", "Main");

    return app.exec();
}
