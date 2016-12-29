#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "blecontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    BLEController bleController;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("bleController", &bleController);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
