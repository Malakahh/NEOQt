#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "blecontroller.h"
#include "chargermodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

//    qmlRegisterType<BluetoothDeviceDataObject>("com.neo", 1, 0, "BluetoothDeviceDataObject");

    BLEController& bleController = BLEController::getInstance();
    ChargerModel chargerModel;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("bleController", &bleController);
    engine.rootContext()->setContextProperty("chargerModel", &chargerModel);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
