#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "bluetoothcontroller.h"
#include <QQuickView>
#include <QQmlContext>
#include <qfileinfo.h>
#include <QtWidgets/qfilesystemmodel.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    BluetoothController btController;
    QFileSystemModel fsModel;
    fsModel.setRootPath("/");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("btController", &btController);
    engine.rootContext()->setContextProperty("fsModel", &fsModel);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
