#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include <QStandardPaths>
#include <QDirModel>

#include "blecontroller.h"
#include "chargermodel.h"
#include "filehelper.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    BLEController& bleController = BLEController::getInstance();
    ChargerModel chargerModel;
    FileHelper& fileHelper = FileHelper::getInstance();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("bleController", &bleController);
    engine.rootContext()->setContextProperty("chargerModel", &chargerModel);
    engine.rootContext()->setContextProperty("fileHelper", &fileHelper);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
