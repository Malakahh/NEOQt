#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include <QFileSystemModel>

#include "blecontroller.h"
#include "chargermodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);
    //QCoreApplication app(argc, argv);

//    qmlRegisterType<BluetoothDeviceDataObject>("com.neo", 1, 0, "BluetoothDeviceDataObject");

    BLEController& bleController = BLEController::getInstance();
    ChargerModel chargerModel;
    QFileSystemModel fsModel;
    fsModel.setRootPath("/");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("bleController", &bleController);
    engine.rootContext()->setContextProperty("chargerModel", &chargerModel);
    engine.rootContext()->setContextProperty("fsModel", &fsModel);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
