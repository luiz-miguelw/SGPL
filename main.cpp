#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>           // Permite injetar variáveis C++ no QML
#include "catalogocontroller.h"  // O controlador que acabamos de criar

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    CatalogoController catalogoController;
    engine.rootContext()->setContextProperty("catalogo", &catalogoController);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("SGPL", "Main");

    return app.exec();
}
