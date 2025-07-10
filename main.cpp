#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Model.hpp"

int main(int argc, char* argv[])
{
    QGuiApplication app{ argc, argv };

    QQmlApplicationEngine engine{};

    Model model{};
    engine.rootContext()->setContextProperty("listModel", &model);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("MobileOperators", "Main");

    return app.exec();
}
