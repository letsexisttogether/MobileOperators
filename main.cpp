#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Model/CombinedModel.hpp"

int main(int argc, char* argv[])
{
    QGuiApplication app{ argc, argv };

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
