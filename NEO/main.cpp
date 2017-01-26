#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include <QStandardPaths>
#include <QDirModel>

#include "blecontroller.h"
#include "chargermodel.h"
#include "filebrowsermodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);
    //QCoreApplication app(argc, argv);

//    qmlRegisterType<BluetoothDeviceDataObject>("com.neo", 1, 0, "BluetoothDeviceDataObject");

    BLEController& bleController = BLEController::getInstance();
    ChargerModel chargerModel;
    FileBrowserModel fbModel;
    //fbModel.setRootPath(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).last());

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("bleController", &bleController);
    engine.rootContext()->setContextProperty("chargerModel", &chargerModel);
    engine.rootContext()->setContextProperty("fbModel", &fbModel);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
