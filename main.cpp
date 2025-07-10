#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "SQL/SqlManager.hpp"
#include "Model/CombinedModel.hpp"

int main(int argc, char* argv[])
{
    QGuiApplication app{ argc, argv };

    SqlManager::Init("QSQLITE", "D:\\Projects\\MobileOperators\\OM system.db");

    QQmlApplicationEngine engine{};

    CombinedModel model{};
    engine.rootContext()->setContextProperty("combinedModel", &model);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("MobileOperators", "Main");

    return app.exec();
}
